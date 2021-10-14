#include "../reader.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Reader, Read) {
    const std::vector<char> expected_data = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', '\n',
        'k', 'k', 'k', ' ', 'a', '.'
    };
    Reader reader("./mock/test_1.txt");
    for (size_t i = 0; i < expected_data.size(); ++i) {
        ASSERT_TRUE(reader.HasNextByte());
        auto read_byte = reader.ReadNextByte();
        ASSERT_EQ(read_byte, expected_data[i]);
    }

    ASSERT_FALSE(reader.HasNextByte());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
