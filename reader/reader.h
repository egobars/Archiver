#include <fstream>
#include <string>
#include <vector>

class Reader {
public:
    Reader(const std::string& file_path);
    ~Reader();
    unsigned char ReadNextByte();
    bool HasNextByte();
    void SetToStart();

private:
    std::ifstream file_;
    size_t file_size_ = 0;
    size_t bytes_read_ = 0;
};
