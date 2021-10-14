#include <iostream>
#include "reader.h"

Reader::Reader(const std::string& file_path) {
    file_.open(file_path);
    if (!file_) {
        std::cout << "Can't open requested file: " << file_path << std::endl;
        exit(0);
    }
    file_.seekg(0, std::ios::end);
    file_size_ = file_.tellg();
    file_.seekg(0);
}

Reader::~Reader() {
    if (file_.is_open()) {
        file_.close();
    }
}

unsigned char Reader::ReadNextByte() {
    char symbol;
    file_.read(&symbol, 1);
    ++bytes_read_;
    return symbol;
}

bool Reader::HasNextByte() {
    return bytes_read_ < file_size_;
}

void Reader::SetToStart() {
    file_.seekg(0, std::ios::beg);
    bytes_read_ = 0;
}
