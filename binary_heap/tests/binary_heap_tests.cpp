#include "../binary_heap.h"
#include <gtest/gtest.h>
#include <vector>

TEST(BinaryHeap, AddExtract) {
    BinaryHeap binary_heap;
    binary_heap.Insert({2, 0});
    binary_heap.Insert({3, 2});
    binary_heap.Insert({1, 1});
    ASSERT_EQ(1, binary_heap.ExtractMin().count);
    ASSERT_EQ(2, binary_heap.GetSize());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
