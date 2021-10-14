#include <vector>
#include <string>

class Trie {
public:
    struct CodeSymbol {
        std::string code;
        int symbol = 0;
        bool operator <(const CodeSymbol& other);
    };
    Trie();
    Trie(const std::vector<CodeSymbol>& trie_data);
    size_t AddTerminalVertex(int symbol);
    size_t AddVertex(size_t left_son, size_t right_son);
    std::vector<CodeSymbol> GetAllTerminalWays();
    bool IsTerminal(size_t vertex);
    int GetSymbol(size_t vertex);
    size_t GoToRoot();
    size_t GoLeft(size_t vertex);
    size_t GoRight(size_t vertex);

private:
    struct Vertex {
        bool is_terminal = false;
        int symbol = 0;
        size_t index = 0;
        size_t left_son = 0;
        size_t right_son = 0;
        size_t subtree_size = 1;
    };
    void Dfs(size_t vertex, std::string& current_code, std::vector<CodeSymbol>& result);
    std::vector<Vertex> trie_;
    int64_t root_ = -1;
};
