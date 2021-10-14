#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include "archiver_main.h"
#include "../binary_heap/binary_heap.h"
#include "../trie/trie.h"

Archiver::Archiver() {

};

void Archiver::AddByte(unsigned char &byte, int &len, bool bit, Writer& writer) {
    if (bit) {
        byte |= (1 << len);
    }
    ++len;
    if (len == 8) {
        writer.WriteByte(byte);
        byte = 0;
        len = 0;
    }
}

int Archiver::GetNineBits(unsigned char &byte, int &len, Reader &reader) {
    int nine_bits = 0;
    for (int i = 0; i < 9; ++i) {
        if (len == 0) {
            if (!reader.HasNextByte()) {
                std::cout << "The archiver file has an incorrect format. Maybe it was corrupted?" << std::endl;
                exit(0);
            }
            byte = reader.ReadNextByte();
        }
        bool bit = (1 << len) & byte;
        ++len;
        if (len == 8) {
            len = 0;
        }
        if (bit) {
            nine_bits |= (1 << i);
        }
    }
    return nine_bits;
}

void Archiver::Archive(const std::string &archive_file, const std::vector<std::string> &files_to_archive) {
    Writer writer(archive_file);
    for (size_t now_file = 0; now_file < files_to_archive.size(); ++now_file) {
        Reader reader(files_to_archive[now_file]);
        std::map<int, size_t> symbols_count;
        for (unsigned char symbol : files_to_archive[now_file]) {
            ++symbols_count[symbol];
        }
        while (reader.HasNextByte()) {
            ++symbols_count[reader.ReadNextByte()];
        }
        ++symbols_count[FILENAME_END_];
        ++symbols_count[ONE_MORE_FILE_];
        ++symbols_count[ARCHIVE_END_];
        Trie trie;
        BinaryHeap binary_heap;
        for (const std::pair<size_t, size_t> kpv : symbols_count) {
            size_t symbol;
            size_t count;
            std::tie(symbol, count) = kpv;
            size_t index = trie.AddTerminalVertex(symbol);
            binary_heap.Insert({count, index});
        }
        while (binary_heap.GetSize() > 1) {
            BinaryHeap::CountIndex first = binary_heap.ExtractMin();
            BinaryHeap::CountIndex second = binary_heap.ExtractMin();
            size_t index = trie.AddVertex(first.index, second.index);
            binary_heap.Insert({first.count + second.count, index});
        }
        std::vector<Trie::CodeSymbol> codes = trie.GetAllTerminalWays();
        std::sort(codes.begin(), codes.end());
        std::vector<bool> now_code;
        std::vector<int> number_symbols_with_len;
        std::map<int, std::vector<bool>> canon_code;
        for (const Trie::CodeSymbol& code_symbol : codes) {
            size_t len = code_symbol.code.size();
            while (now_code.size() < len) {
                now_code.push_back(0);
                number_symbols_with_len.push_back(0);
            }
            canon_code[code_symbol.symbol] = now_code;
            ++number_symbols_with_len[now_code.size() - 1];
            bool is_changed = false;
            for (int64_t i = now_code.size() - 1; i >= 0; --i) {
                if (now_code[i] == 0) {
                    now_code[i] = 1;
                    is_changed = true;
                    break;
                }
                now_code[i] = 0;
            }
            if (!is_changed) {
                now_code.push_back(0);
                now_code[0] = 1;
                number_symbols_with_len.push_back(0);
            }
        }
        while (!number_symbols_with_len.empty() && number_symbols_with_len.back() == 0) {
            number_symbols_with_len.pop_back();
        }
        unsigned char byte = 0;
        int len = 0;
        for (int i = 0; i < 9; ++i) {
            AddByte(byte, len, symbols_count.size() & (1 << i), writer);
        }
        for (const Trie::CodeSymbol& code_symbol : codes) {
            for (int i = 0; i < 9; ++i) {
                AddByte(byte, len, code_symbol.symbol & (1 << i), writer);
            }
        }
        for (size_t i = 0; i < number_symbols_with_len.size(); ++i) {
            for (int j = 0; j < 9; ++j) {
                AddByte(byte, len, number_symbols_with_len[i] & (1 << j), writer);
            }
        }
        if (len != 0) {
            writer.WriteByte(byte);
            len = 0;
            byte = 0;
        }
        for (unsigned char symbol : files_to_archive[now_file]) {
            for (bool bit: canon_code[symbol]) {
                AddByte(byte, len, bit, writer);
            }
        }
        for (bool bit: canon_code[FILENAME_END_]) {
            AddByte(byte, len, bit, writer);
        }
        reader.SetToStart();
        while (reader.HasNextByte()) {
            unsigned char symbol = reader.ReadNextByte();
            for (bool bit: canon_code[symbol]) {
                AddByte(byte, len, bit, writer);
            }
        }
        if (now_file != files_to_archive.size() - 1) {
            for (bool bit: canon_code[ONE_MORE_FILE_]) {
                AddByte(byte, len, bit, writer);
            }
        }
        if (now_file == files_to_archive.size() - 1) {
            for (bool bit: canon_code[ARCHIVE_END_]) {
                AddByte(byte, len, bit, writer);
            }
        }
        if (len != 0) {
            writer.WriteByte(byte);
        }
    }
}

void Archiver::Dearchive(const std::string &archive_file) {
    Reader reader(archive_file);
    bool is_file_ended = false;
    while (!is_file_ended) {
        unsigned char byte = 0;
        int len = 0;
        ArchiveData archive_data;
        archive_data.symbols_count = GetNineBits(byte, len, reader);
        for (int i = 0; i < archive_data.symbols_count; ++i) {
            archive_data.alphabet_symbols.push_back(GetNineBits(byte, len, reader));
        }
        int symbols_with_non_zero_count = 0;
        while (symbols_with_non_zero_count < archive_data.symbols_count) {
            int value = GetNineBits(byte, len, reader);
            archive_data.number_symbols_with_len.push_back(value);
            symbols_with_non_zero_count += value;
        }
        std::vector<Trie::CodeSymbol> codes;
        for (int i = 0; i < archive_data.symbols_count; ++i) {
            codes.push_back({"", archive_data.alphabet_symbols[i]});
        }
        std::vector<bool> now_code;
        int viewed_symbols = 0;
        for (size_t i = 0; i < archive_data.number_symbols_with_len.size(); ++i) {
            while (now_code.size() < i + 1) {
                now_code.push_back(0);
            }
            for (int j = 0; j < archive_data.number_symbols_with_len[i]; ++j) {
                std::string now_code_str;
                for (bool number : now_code) {
                    if (number) {
                        now_code_str += '1';
                    } else {
                        now_code_str += '0';
                    }
                }
                codes[viewed_symbols].code = now_code_str;
                ++viewed_symbols;
                bool is_changed = false;
                for (int64_t k = now_code.size() - 1; k >= 0; --k) {
                    if (now_code[k] == 0) {
                        now_code[k] = 1;
                        is_changed = true;
                        break;
                    }
                    now_code[k] = 0;
                }
                if (!is_changed) {
                    now_code.push_back(0);
                    now_code[0] = 1;
                }
            }
        }
        Trie trie(codes);
        size_t current_vertex = trie.GoToRoot();
        bool is_name = true;
        bool now_file_end = false;
        Writer writer;
        std::string name;
        while (!now_file_end) {
            if (!reader.HasNextByte()) {
                std::cout << "The archiver file has an incorrect format. Maybe it was corrupted?" << std::endl;
                if (!is_name) {
                    writer.~Writer();
                    remove(name.c_str());
                }
                exit(0);
            }
            int now_byte = reader.ReadNextByte();
            for (int j = 0; j < 8; ++j) {
                bool bit = now_byte & (1 << j);
                if (bit) {
                    current_vertex = trie.GoRight(current_vertex);
                } else {
                    current_vertex = trie.GoLeft(current_vertex);
                }
                if (trie.IsTerminal(current_vertex)) {
                    int symbol = trie.GetSymbol(current_vertex);
                    current_vertex = trie.GoToRoot();
                    if (symbol == FILENAME_END_) {
                        writer.OpenFile(name);
                        is_name = false;
                    } else if (symbol == ONE_MORE_FILE_) {
                        now_file_end = true;
                        break;
                    } else if (symbol == ARCHIVE_END_) {
                        now_file_end = true;
                        is_file_ended = true;
                        break;
                    } else {
                        if (is_name) {
                            name += static_cast<unsigned char>(symbol);
                        } else {
                            writer.WriteByte(static_cast<unsigned char>(symbol));
                        }
                    }
                }
            }
        }
    }
}

void Archiver::Help() {
    std::cout << "Archiver build 1.0" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "archiver -c archive_name file1 [file2 ...]  -  archive file1, file2, ... to archive_name." << std::endl;
    std::cout << "archiver -d archive_name  -  dearchive archive_name." << std::endl;
    std::cout << "archiver -h  -  help." << std::endl;
}
