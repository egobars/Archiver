#include <fstream>
#include <string>
#include <vector>

class Writer {
public:
    Writer();
    Writer(const std::string& file_path);
    ~Writer();
    void OpenFile(const std::string& file_path);
    void WriteByte(unsigned char byte);

private:
    std::ofstream file_;
};