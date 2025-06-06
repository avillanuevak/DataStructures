#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>
#include <functional>
#include <algorithm>

template <typename T, typename Compare = std::less<T>>
class MinHeap {
private:
    std::vector<T> heap;
    Compare comp;

    // Helper functions
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }

    void heapifyUp(size_t i) {
        while (i > 0 && comp(heap[i], heap[parent(i)])) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(size_t i) {
        size_t minIndex = i;
        size_t l = left(i);
        size_t r = right(i);
        
        if (l < heap.size() && comp(heap[l], heap[minIndex]))
            minIndex = l;
            
        if (r < heap.size() && comp(heap[r], heap[minIndex]))
            minIndex = r;
            
        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            heapifyDown(minIndex);
        }
    }

public:
    MinHeap() = default;
    explicit MinHeap(const Compare& cmp) : comp(cmp) {}
    
    explicit MinHeap(const std::vector<T>& elements) : heap(elements) {
        for (int i = static_cast<int>(size())/2 - 1; i >= 0; --i)
            heapifyDown(static_cast<size_t>(i));
    }

    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    T pop() {
        if (empty()) throw std::out_of_range("Heap is empty");
        T root = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        if (!empty()) heapifyDown(0);
        return root;
    }

    const T& top() const {
        if (empty()) throw std::out_of_range("Heap is empty");
        return heap.front();
    }

    bool empty() const { return heap.empty(); }
    size_t size() const { return heap.size(); }

    void decreaseKey(size_t i, const T& newValue) {
        if (i >= heap.size()) throw std::out_of_range("Index out of range");
        if (comp(heap[i], newValue)) 
            throw std::invalid_argument("New value is not smaller");
        
        heap[i] = newValue;
        heapifyUp(i);
    }

    void clear() { heap.clear(); }
};

#endif // MINHEAP_H