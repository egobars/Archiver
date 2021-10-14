#include "../trie.h"
#include <gtest/gtest.h>
#include <vector>

TEST(Trie, EmptyTrie) {
    const std::vector<Trie::CodeSymbol> expected_data = {
        {"0", 'a'}, {"1", 'b'}
    };
    Trie trie;
    int left_vertex = trie.AddTerminalVertex('a');
    int right_vertex = trie.AddTerminalVertex('b');
    trie.AddVertex(left_vertex, right_vertex);
    std::vector<Trie::CodeSymbol> codes = trie.GetAllTerminalWays();
    ASSERT_EQ(codes.size(), expected_data.size());
    for (size_t i = 0; i < codes.size(); ++i) {
        ASSERT_EQ(codes[i].code, expected_data[i].code);
        ASSERT_EQ(codes[i].symbol, expected_data[i].symbol);
    }
}

TEST(Trie, FullTrie) {
    Trie trie({{"0", 'a'}, {"1", 'b'}});
    int vertex = trie.GoToRoot();
    vertex = trie.GoLeft(vertex);
    ASSERT_TRUE(trie.IsTerminal(vertex));
    ASSERT_EQ(trie.GetSymbol(vertex), 'a');
    vertex = trie.GoToRoot();
    vertex = trie.GoRight(vertex);
    ASSERT_TRUE(trie.IsTerminal(vertex));
    ASSERT_EQ(trie.GetSymbol(vertex), 'b');
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
