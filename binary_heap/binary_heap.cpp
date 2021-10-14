#include <cstdint>
#include "binary_heap.h"

BinaryHeap::BinaryHeap() {

}

void BinaryHeap::SiftDown(int64_t vertex) {
    while (static_cast<size_t>(2 * vertex + 1) < heap_.size()) {
        int64_t left_son = 2 * vertex + 1;
        int64_t right_son = 2 * vertex + 2;
        int64_t new_vertex = left_son;
        if (static_cast<size_t>(right_son) < heap_.size() && heap_[right_son].count < heap_[left_son].count) {
            new_vertex = right_son;
        }
        if (heap_[vertex].count <= heap_[new_vertex].count) {
            break;
        }
        std::swap(heap_[vertex], heap_[new_vertex]);
        vertex = new_vertex;
    }
}

void BinaryHeap::SiftUp(int64_t vertex) {
    while (heap_[vertex].count < heap_[(vertex - 1) / 2].count) {
        std::swap(heap_[vertex], heap_[(vertex - 1) / 2]);
        vertex = (vertex - 1) / 2;
    }
}

BinaryHeap::CountIndex BinaryHeap::ExtractMin() {
    CountIndex min = heap_[0];
    heap_[0] = heap_.back();
    heap_.pop_back();
    SiftDown(0);
    return min;
}

void BinaryHeap::Insert(CountIndex key) {
    heap_.push_back(key);
    SiftUp(heap_.size() - 1);
}

size_t BinaryHeap::GetSize() {
    return heap_.size();
}
