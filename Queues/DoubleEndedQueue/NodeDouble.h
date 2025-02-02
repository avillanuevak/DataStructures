#include <iostream>
using namespace std;

/**
 * @class NodeDoble
 * @brief A template class representing a node in a double-ended queue.
 * 
 * @tparam E The type of the element stored in the node.
 * 
 * This class encapsulates an element and pointers to the next and previous nodes
 * in a double-ended queue (deque). It provides methods to access and modify these
 * pointers and the stored element.
 * 
 * @note The complexity of all member functions is O(1) as they involve simple 
 * pointer manipulations or element access.
 */
template <class E>
class NodeDoble
{
    private:
        E element; ///< The element stored in the node.
        NodeDoble<E>* next; ///< Pointer to the next node.
        NodeDoble<E>* previous; ///< Pointer to the previous node.

    public:
        /**
         * @brief Constructor that initializes the node with the given element.
         * @param element The element to be stored in the node.
         * @note Complexity: O(1)
         */
        NodeDoble(E element): element(element), next(nullptr), previous(nullptr){}

        /**
         * @brief Returns a constant reference to the stored element.
         * @return A constant reference to the element stored in the node.
         * @note Complexity: O(1)
         */
        const E& getElement(){
            return element;
        }

        /**
         * @brief Returns a pointer to the next node.
         * @return A pointer to the next node in the deque.
         * @note Complexity: O(1)
         */
        NodeDoble<E>* getNext(){
            return next;
        }

        /**
         * @brief Sets the pointer to the next node.
         * @param next A pointer to the node that should be the next node.
         * @note Complexity: O(1)
         */
        void setNext(NodeDoble<E>* next){
            this->next = next;
        }

        /**
         * @brief Returns a pointer to the previous node.
         * @return A pointer to the previous node in the deque.
         * @note Complexity: O(1)
         */
        NodeDoble<E>* getPrevious(){
            return previous;
        }
        
        /**
         * @brief Sets the pointer to the previous node.
         * @param previous A pointer to the node that should be the previous node.
         * @note Complexity: O(1)
         */
        void setPrevious(NodeDoble<E>* previous){
            this->previous = previous;
        }
};