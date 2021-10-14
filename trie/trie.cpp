#include <iostream>
#include <tuple>
#include "trie.h"

Trie::Trie() {

}

Trie::Trie(const std::vector<CodeSymbol>& trie_data) {
    root_ = 0;
    trie_.push_back({false, 0, 0, 0, 0, 0});
    size_t current_vertex = root_;
    for (const CodeSymbol& code_symbol : trie_data) {
        std::string code = code_symbol.code;
        for (char ch : code) {
            if (ch == '0') {
                if (trie_[current_vertex].left_son != 0) {
                    current_vertex = trie_[current_vertex].left_son;
                } else {
                    trie_[current_vertex].left_son = trie_.size();
                    current_vertex = trie_.size();
                    trie_.push_back({false, 0, trie_.size(), 0, 0, 0});
                }
            } else {
                if (trie_[current_vertex].right_son != 0) {
                    current_vertex = trie_[current_vertex].right_son;
                } else {
                    trie_[current_vertex].right_son = trie_.size();
                    current_vertex = trie_.size();
                    trie_.push_back({false, 0, trie_.size(), 0, 0, 0});
                }
            }
        }
        trie_[current_vertex].is_terminal = true;
        trie_[current_vertex].symbol = code_symbol.symbol;
        current_vertex = root_;
    }
}

bool Trie::IsTerminal(size_t vertex) {
    return trie_[vertex].is_terminal;
}

int Trie::GetSymbol(size_t vertex) {
    return trie_[vertex].symbol;
}

size_t Trie::GoToRoot() {
    return root_;
}

size_t Trie::GoLeft(size_t vertex) {
    return trie_[vertex].left_son;
}

size_t Trie::GoRight(size_t vertex) {
    return trie_[vertex].right_son;
}

size_t Trie::AddTerminalVertex(int symbol) {
    Vertex new_vertex;
    new_vertex.is_terminal = true;
    new_vertex.symbol = symbol;
    new_vertex.index = trie_.size();
    trie_.push_back(new_vertex);
    return new_vertex.index;
}

size_t Trie::AddVertex(size_t left_son, size_t right_son) {
    Vertex new_vertex;
    new_vertex.is_terminal = false;
    new_vertex.index = trie_.size();
    new_vertex.left_son = left_son;
    new_vertex.right_son = right_son;
    new_vertex.subtree_size = trie_[left_son].subtree_size + trie_[right_son].subtree_size + 1;
    root_ = new_vertex.index;
    trie_.push_back(new_vertex);
    return new_vertex.index;
}

void Trie::Dfs(size_t vertex, std::string& current_code, std::vector<Trie::CodeSymbol>& result) {
    if (trie_[vertex].is_terminal) {
        result.push_back({current_code, trie_[vertex].symbol});
    } else {
        current_code.push_back('0');
        Dfs(trie_[vertex].left_son, current_code, result);
        current_code.pop_back();
        current_code.push_back('1');
        Dfs(trie_[vertex].right_son, current_code, result);
        current_code.pop_back();
    }
}

std::vector<Trie::CodeSymbol> Trie::GetAllTerminalWays() {
    std::vector<CodeSymbol> result;
    std::string current_code;
    Dfs(root_, current_code, result);
    return result;
}

bool Trie::CodeSymbol::operator<(const CodeSymbol& other) {
    if (code.size() != other.code.size()) {
        return code.size() < other.code.size();
    }
    return code < other.code;
}
