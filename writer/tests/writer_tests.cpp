#include "../writer.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Writer, Write) {
    const std::vector<char> expected_data = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', '\n',
        'k', 'k', 'k', ' ', 'a', '.'
    };
    Writer writer("./mock/test_1.txt");
    for (size_t i = 0; i < expected_data.size(); ++i) {
        writer.WriteByte(expected_data[i]);
    }
    writer.~Writer();
    std::ifstream file;
    file.open("./mock/test_1.txt");
    for (size_t i = 0; i < expected_data.size(); ++i) {
        char symbol;
        file.read(&symbol, 1);
        ASSERT_EQ(symbol, expected_data[i]);
    }
    file.close();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
