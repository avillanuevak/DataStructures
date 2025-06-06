#include "MinHeap.h"
#include <iostream>
#include <string>

int main() {
    // Test 1: Basic integer heap
    MinHeap<int> intHeap;
    intHeap.push(30);
    intHeap.push(10);
    intHeap.push(20);
    intHeap.push(5);
    intHeap.push(15);

    std::cout << "=== Integer MinHeap Test ===" << std::endl;
    std::cout << "Top: " << intHeap.top() << std::endl;
    std::cout << "Size: " << intHeap.size() << std::endl;
    
    std::cout << "Popping elements: ";
    while (!intHeap.empty()) {
        std::cout << intHeap.pop() << " ";
    }
    std::cout << "\n\n";

    // Test 2: Heap construction from vector
    std::vector<double> vals = {5.5, 1.1, 3.3, 2.2, 4.4};
    MinHeap<double> doubleHeap(vals);
    
    std::cout << "=== Double Heap from Vector ===" << std::endl;
    std::cout << "Top: " << doubleHeap.top() << std::endl;
    doubleHeap.push(0.5);
    std::cout << "New top after push: " << doubleHeap.top() << std::endl;
    std::cout << "Popping: " << doubleHeap.pop() << std::endl;
    std::cout << "New top: " << doubleHeap.top() << "\n\n";

    // Test 3: Custom comparator (Max heap)
    MinHeap<int, std::greater<int>> maxHeap;
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    
    std::cout << "=== MaxHeap Test ===" << std::endl;
    std::cout << "Top: " << maxHeap.top() << std::endl;
    std::cout << "Popping: " << maxHeap.pop() << std::endl;
    std::cout << "New top: " << maxHeap.top() << "\n\n";

    // Test 4: String heap
    MinHeap<std::string> strHeap;
    strHeap.push("banana");
    strHeap.push("apple");
    strHeap.push("cherry");
    
    std::cout << "=== String Heap Test ===" << std::endl;
    std::cout << "Top: " << strHeap.top() << std::endl;
    strHeap.push("apricot");
    std::cout << "New top: " << strHeap.top() << std::endl;

    // Test 5: Edge cases
    MinHeap<int> emptyHeap;
    try {
        emptyHeap.pop();
    } catch (const std::exception& e) {
        std::cout << "\n=== Exception Test ===" << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}