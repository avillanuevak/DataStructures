#include <iostream>
#include "NodeDouble.h"
#include <stdexcept>
using namespace std;

template <class Element>
class DoubleEndedQueue
{
    private:
        NodeDoble<Element>* front; ///< Pointer to the front node.
        NodeDoble<Element>* rear; ///< Pointer to the rear node.
        int size; ///< The number of elements in the queue.
        
    public:
        /**
         * @brief Default constructor that initializes an empty queue.
         * @note Complexity: O(1)
         */
        DoubleEndedQueue(): size(0){
            front = nullptr;
            rear = nullptr;
        }

        /**
         * @brief Copy constructor.
         * @param q The queue to copy.
         * @note Complexity: O(n)
         */
        DoubleEndedQueue(const DoubleEndedQueue<Element>& q) : front(nullptr), rear(nullptr), size(0) {
            NodeDoble<Element>* current = q.front;
            while (current != nullptr) {
                insertRear(current->getElement());
                current = current->getNext();
            }
        }

        /**
         * @brief Destructor that deallocates all nodes in the queue.
         * @note Complexity: O(n)
         */
        virtual ~DoubleEndedQueue(){
            while (!isEmpty()) {
                removeFront();
            }
        }

        /**
         * @brief Copy assignment operator.
         * @param q The queue to assign.
         * @return Reference to the assigned queue.
         * @note Complexity: O(n)
         */
        DoubleEndedQueue& operator=(const DoubleEndedQueue<Element>& q) {
            if (this != &q) {
                DoubleEndedQueue<Element> temp(q);
                swap(temp);
            }
            return *this;
        }

        /**
         * @brief Swaps the contents of this queue with another queue.
         * @param other The queue to swap with.
         * @note Complexity: O(1)
         */
        void swap(DoubleEndedQueue<Element>& other) noexcept {
            std::swap(front, other.front);
            std::swap(rear, other.rear);
            std::swap(size, other.size);
        }

        /**
         * @brief Inserts an element at the rear of the queue.
         * @param element The element to be inserted.
         * @note Complexity: O(1)
         */
        void insertRear(const Element& element){
            NodeDoble<Element>* n = new NodeDoble<Element>(element);
            if (isEmpty()){
                front = n;
                rear = n;
                size++;
            }
            else{
                n->setPrevious(rear);
                rear->setNext(n);
                rear = n;
                size++;
            }
        }

        /**
         * @brief Inserts an element at the front of the queue.
         * @param element The element to be inserted.
         * @note Complexity: O(1)
         */
        void insertFront(const Element& element){
            NodeDoble<Element>* n = new NodeDoble<Element>(element);
            if (isEmpty()){
                front = n;
                rear = n;
                size++;
            }
            else{
                n->setNext(front);
                front->setPrevious(n);
                front = n;
                size++;
            }
        }

        /**
         * @brief Removes an element from the rear of the queue.
         * @note Complexity: O(1)
         */
        void removeRear(){
            if (isEmpty()) throw logic_error("The queue is empty.\n");
            else{
                NodeDoble<Element>* temp = rear;
                cout << "Removing element: " << temp->getElement() << endl; // Debug statement
                rear = rear->getPrevious();
                if (rear != nullptr) {
                    rear->setNext(nullptr);
                } else {
                    front = nullptr; // If the queue becomes empty
                }
                delete temp;
                size--;
                cout << "Element removed. New rear: " << (rear ? to_string(rear->getElement()) : "nullptr") << endl; // Debug statement
            }
        }

        /**
         * @brief Removes an element from the front of the queue.
         * @note Complexity: O(1)
         */
        void removeFront(){
            if (isEmpty()) throw logic_error("The queue is empty.\n");
            NodeDoble<Element>* temp = front->getNext();
            delete front;
            front = temp;
            if (front != nullptr) {
                front->setPrevious(nullptr);
            } else {
                rear = nullptr; // If the queue becomes empty
            }
            size--;
        }

        /**
         * @brief Checks if the queue is empty.
         * @return True if the queue is empty, false otherwise.
         * @note Complexity: O(1)
         */
        bool isEmpty() const{
            return (size == 0);
        }

        /**
         * @brief Prints the elements of the queue from front to rear.
         * @note Complexity: O(n)
         */
        void print() const{
            if (isEmpty()){
                throw logic_error("The queue is empty.\n");
            }
            NodeDoble<Element>* temp = front;
            cout << "[ ";
            while (temp != nullptr){
                cout << temp->getElement() << " ";
                temp = temp->getNext();
            }
            cout << "]\n";
        }

        /**
         * @brief Prints the elements of the queue from rear to front.
         * @note Complexity: O(n)
         */
        void printRear() const{
            if (isEmpty()){
                throw logic_error("The queue is empty.\n");
            }
            NodeDoble<Element>* temp = rear;
            cout << "[ ";
            while (temp != nullptr){
                cout << temp->getElement() << " ";
                temp = temp->getPrevious();
            }
            cout << "]\n";
        }

        /**
         * @brief Returns the element at the rear of the queue.
         * @return A constant reference to the element at the rear.
         * @note Complexity: O(1)
         */
        const Element& getRear() const{
            if (isEmpty()) throw logic_error("The queue is empty.\n");
            return rear->getElement();
        }

        /**
         * @brief Returns the element at the front of the queue.
         * @return A constant reference to the element at the front.
         * @note Complexity: O(1)
         */
        const Element& getFront() const{
            if (isEmpty()) throw logic_error("The queue is empty.\n");
            return front->getElement();
        }

        /**
         * @brief Returns the number of elements in the queue.
         * @return The size of the queue.
         * @note Complexity: O(1)
         */
        int getSize() const{
            return size;
        }
};