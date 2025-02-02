#include <stdexcept>

/**
 * @class Queue
 * @brief A template class for a static queue implementation.
 * 
 * This class provides a static queue implementation with basic operations such as enqueue, dequeue, 
 * and checking if the queue is empty or full.
 * 
 * @tparam E The type of elements stored in the queue.
 */
template <typename E>
class Queue {
private:
    int capacity; ///< The maximum number of elements the queue can hold.
    int front; ///< The index of the front element in the queue.
    int rear; ///< The index of the rear element in the queue.
    E* data; ///< Pointer to the array that holds the queue elements.
public:
    /**
     * @brief Constructor to initialize the queue with a given capacity.
     * 
     * @param capacity The maximum number of elements the queue can hold.
     * 
     * @complexity O(1)
     */
    Queue(int capacity);

    /**
     * @brief Destructor to clean up the allocated memory.
     * 
     * @complexity O(1)
     */
    ~Queue();

    /**
     * @brief Get the current number of elements in the queue.
     * 
     * @return The number of elements in the queue.
     * 
     * @complexity O(1)
     */
    int size();

    /**
     * @brief Add an element to the rear of the queue.
     * 
     * @param e The element to be added to the queue.
     * 
     * @complexity O(1)
     */
    void enqueue(const E& e);

    /**
     * @brief Remove and return the front element from the queue.
     * 
     * @return The front element of the queue.
     * 
     * @complexity O(1)
     */
    E dequeue();

    /**
     * @brief Get the front element of the queue without removing it.
     * 
     * @return The front element of the queue.
     * 
     * @complexity O(1)
     */
    E frontValue() const;

    /**
     * @brief Check if the queue is empty.
     * 
     * @return True if the queue is empty, false otherwise.
     * 
     * @complexity O(1)
     */
    bool isEmpty() const;

    /**
     * @brief Check if the queue is full.
     * 
     * @return True if the queue is full, false otherwise.
     * 
     * @complexity O(1)
     */
    bool isFull() const;
};

template <typename E>
Queue<E>::Queue(int capacity) {
    this->capacity = capacity;
    front = 0;
    rear = 0;
    data = new E[capacity];
}

template <typename E>
Queue<E>::~Queue() {
    delete[] data;
}

template  <typename E>
int Queue<E>::size(){
    return capacity;
}

template <typename E>
void Queue<E>::enqueue(const E& e) {
    if (!isFull()) {
        data[rear] = e;
        rear = (rear + 1) % capacity;
    }
}

template <typename E>
E Queue<E>::frontValue() const {
    if (!isEmpty()) {
        return data[front];
    }
    throw std::runtime_error("Queue is empty");
}

template <typename E>
E Queue<E>::dequeue() {
    if (!isEmpty()) {
        E e = data[front];
        front = (front + 1) % capacity;
        return e;
    }
    throw std::runtime_error("Queue is empty");
}

template <typename E>
bool Queue<E>::isEmpty() const {
    return front == rear;
}

template <typename E>
bool Queue<E>::isFull() const {
    return (rear + 1) % capacity == front;
}