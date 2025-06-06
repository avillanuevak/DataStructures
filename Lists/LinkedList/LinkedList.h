// LinkedList.h
// Time and Space Complexity:
// - insertFront, insertBack, insertAfter, insertBefore: O(1) time, O(1) space per operation.
// - removeFront, removeBack, remove: O(1) time, O(1) space per operation.
// - first, last, next, previous: O(1) time.
// - getSize, isEmpty: O(1) time.
// - print: O(n) time, where n is the number of elements.
// The list uses O(n) space for n elements.

#include "Node.h"
#include "Position.h"
#include <initializer_list>
#include <iostream>
#include <stdexcept>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class Element>
class LinkedList{
    public:

        LinkedList();
        LinkedList(std::initializer_list<Element> elements);
        virtual ~LinkedList();

        int getSize() const;
        bool isEmpty() const;
        bool begin(Position<Element>& position) const; // True if it is first sentinel
        bool end(Position<Element>& position) const; // True if it is last sentinel

        Position<Element> first() const; // First position
        Position<Element> last() const; // Last position
        Position<Element> next(Position<Element>& position) const;
        Position<Element> previous(Position<Element>& position) const;

        void insertAfter(Position<Element>& position, const Element& element);
        void insertBefore(Position<Element>& position, const Element& element); 
        void insertFront(const Element& element);
        void insertBack(const Element& element);
        void remove(Position<Element>& position);
        void removeFront();
        void removeBack();
        void print();
        

    private:
        NodeList<Element>* head;
        NodeList<Element>* rear;
        int size;
};
#endif