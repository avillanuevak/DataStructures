#include <iostream>
#include "StaticQueue.h"

int main() {
    // Create a queue with a capacity of 5
    Queue<int> q(5);

    // Enqueue elements
    q.enqueue(1); // Time: O(1), Space: O(1)
    q.enqueue(2); // Time: O(1), Space: O(1)
    q.enqueue(3); // Time: O(1), Space: O(1)
    q.enqueue(4); // Time: O(1), Space: O(1)
    q.enqueue(5); // Time: O(1), Space: O(1)

    // Check if the queue is full
    std::cout << "Is full: " << q.isFull() << std::endl; // Time: O(1), Space: O(1)

    // Dequeue elements
    std::cout << "Dequeued: " << q.dequeue() << std::endl; // Time: O(1), Space: O(1)
    std::cout << "Dequeued: " << q.dequeue() << std::endl; // Time: O(1), Space: O(1)

    // Check the front value
    std::cout << "Front value: " << q.frontValue() << std::endl; // Time: O(1), Space: O(1)

    // Check if the queue is empty
    std::cout << "Is empty: " << q.isEmpty() << std::endl; // Time: O(1), Space: O(1)

    // Enqueue more elements
    q.enqueue(6); // Time: O(1), Space: O(1)
    q.enqueue(7); // Time: O(1), Space: O(1)

    // Check the size of the queue
    std::cout << "Queue size: " << q.size() << std::endl; // Time: O(1), Space: O(1)

    // Dequeue all elements
    while (!q.isEmpty()) {
        std::cout << "Dequeued: " << q.dequeue() << std::endl; // Time: O(1), Space: O(1)
    }

    // Final check if the queue is empty
    std::cout << "Is empty: " << q.isEmpty() << std::endl; // Time: O(1), Space: O(1)

    return 0;
}