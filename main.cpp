#include "archiver_main/archiver_main.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    Archiver archiver;
    if (argc == 1) {
        std::cout << "Unknown command! Type -h to help." << std::endl;
    } else {
        std::string command = argv[1];
        if (command == "-h") {
            archiver.Help();
        } else if (command == "-c") {
            if (argc == 2) {
                std::cout << "You didn't type archive's name! Type -h to help." << std::endl;
            } else {
                std::string archive_name = argv[2];
                if (argc == 3) {
                    std::cout << "You didn't select any files! Type -h to help." << std::endl;
                } else {
                    std::vector<std::string> files_to_archive;
                    for (int i = 3; i < argc; ++i) {
                        files_to_archive.push_back(argv[i]);
                    }
                    archiver.Archive(archive_name, files_to_archive);
                }
            }
        } else if (command == "-d") {
            if (argc == 2) {
                std::cout << "You didn't select any files! Type -h to help." << std::endl;
            } else if (argc > 3) {
                std::cout << "You have selected too many files. Type -h to help." << std::endl;
            } else {
                std::string file_to_dearchive = argv[2];
                archiver.Dearchive(file_to_dearchive);
            }
        } else {
            std::cout << "Unknown command! Type -h to help." << std::endl;
        }
    }
    return 0;
}
