#include <cstdint>
#include <vector>

class BinaryHeap {
public:
    struct CountIndex {
        size_t count = 0;
        size_t index = 0;
    };
    BinaryHeap();
    void SiftDown(int64_t vertex);
    void SiftUp(int64_t vertex);
    CountIndex ExtractMin();
    void Insert(CountIndex key);
    size_t GetSize();

private:
    std::vector<CountIndex> heap_;
};