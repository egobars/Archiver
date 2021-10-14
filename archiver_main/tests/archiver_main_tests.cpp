#include "../archiver_main.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Archive, ArchiveAndDearchiveFile) {
    std::ofstream input_file;
    input_file.open("./mock/file_to_archive.txt");
    std::string text = "abc";
    for (char symbol : text) {
        input_file.write(&symbol, 1);
    }
    input_file.close();
    Archiver archiver;
    archiver.Archive("./mock/archive.txt",
                     {"./mock/file_to_archive.txt"});
    remove("./mock/file_to_archive.txt");
    archiver.Dearchive("./mock/archive.txt");
    std::ifstream output_file;
    output_file.open("./mock/file_to_archive.txt");
    ASSERT_TRUE(output_file);
    std::string new_text;
    output_file >> new_text;
    ASSERT_EQ(text, new_text);
    output_file.close();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
