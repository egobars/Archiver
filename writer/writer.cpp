#include <iostream>
#include "writer.h"

Writer::Writer() {

}

Writer::Writer(const std::string &file_path) {
    file_.open(file_path);
    if (!file_) {
        std::cout << "Can't open requested file: " << file_path << std::endl;
        exit(0);
    }
}

Writer::~Writer() {
    if (file_.is_open()) {
        file_.close();
    }
}

void Writer::OpenFile(const std::string &file_path) {
    file_.open(file_path);
}

void Writer::WriteByte(unsigned char byte) {
    char u_byte = static_cast<char>(byte);
    file_.write(&u_byte, 1);
}
