#include <vector>
#include <string>
#include "../reader/reader.h"
#include "../writer/writer.h"

class Archiver {
public:
    struct ArchiveData {
        int symbols_count = 0;
        std::vector<int> alphabet_symbols;
        std::vector<int> number_symbols_with_len;
    };
    Archiver();
    void Archive(const std::string& archive_file, const std::vector<std::string>& files_to_archive);
    void Dearchive(const std::string& archive_file);
    void Help();

private:
    void AddByte(unsigned char& byte, int& len, bool bit, Writer& writer);
    int GetNineBits(unsigned char& byte, int& len, Reader& reader);
    const int FILENAME_END_ = 256;
    const int ONE_MORE_FILE_ = 257;
    const int ARCHIVE_END_ = 258;
};
