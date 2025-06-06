// LinkedList.cpp
// Complexity Summary:
// All insertion and removal operations (front, back, after, before) are O(1) time and space.
// Access operations (first, last, next, previous, getSize, isEmpty) are O(1) time.
// print() is O(n) time, where n is the number of elements.
// The list uses O(n) space for n elements.

#include "LinkedList.h"

template <class Element>
LinkedList<Element>::LinkedList() {
    head = new NodeList<Element>();
    rear = new NodeList<Element>();

    head->setNext(rear);
    rear->setPrevious(head);
    size = 0;
}

template <class Element>
LinkedList<Element>::LinkedList(std::initializer_list<Element> elements) : LinkedList() {
    for (const auto& el : elements)
        insertBack(el);
}

template <class Element>
LinkedList<Element>::~LinkedList() {
    while (!isEmpty()) {
        removeFront();
    }
    delete head;
    delete rear;
}

template <class Element>
int LinkedList<Element>::getSize() const {
    return size;
}

template <class Element>
bool LinkedList<Element>::isEmpty() const {
    return size == 0;
}

template <class Element>
bool LinkedList<Element>::begin(Position<Element>& position) const {
    return Position<Element>(head) != position;
}

template <class Element>
bool LinkedList<Element>::end(Position<Element>& position) const {
    return Position<Element>(rear) != position;
}

template <class Element>
Position<Element> LinkedList<Element>::first() const {
    return Position<Element>(head->getNext());
}

template <class Element>
Position<Element> LinkedList<Element>::last() const {
    return Position<Element>(rear->getPrevious());
}

template <class Element>
Position<Element> LinkedList<Element>::next(Position<Element>& position) const {
    return position.next();
}

template <class Element>
Position<Element> LinkedList<Element>::previous(Position<Element>& position) const {
    return position.previous();
}

template <class Element>
void LinkedList<Element>::insertAfter(Position<Element>& position, const Element& element) {
    NodeList<Element>* curr = new NodeList<Element>();
    curr->setElement(element); // Use setter instead of direct access

    NodeList<Element>* next = position.node->getNext();
    curr->setNext(next);
    curr->setPrevious(position.node);
    position.node->setNext(curr);
    next->setPrevious(curr);

    size++;
}

template <class Element>
void LinkedList<Element>::insertBefore(Position<Element>& position, const Element& element) {
    Position<Element> prev = previous(position);
    insertAfter(prev, element);
}

template <class Element>
void LinkedList<Element>::insertFront(const Element& element) {
    Position<Element> pos(head);
    insertAfter(pos, element);
}

template <class Element>
void LinkedList<Element>::insertBack(const Element& element) {
    Position<Element> pos(rear->getPrevious());
    insertAfter(pos, element);
}

template <class Element>
void LinkedList<Element>::remove(Position<Element>& position) {
    NodeList<Element>* prev = position.node->getPrevious();
    NodeList<Element>* next = position.node->getNext();

    prev->setNext(next);
    next->setPrevious(prev);

    delete position.node;
    size--;
}

template <class Element>
void LinkedList<Element>::removeFront() {
    if (!isEmpty()) {
        Position<Element> pos = first();
        remove(pos);
    }
}

template <class Element>
void LinkedList<Element>::removeBack() {
    if (!isEmpty()) {
        Position<Element> pos = last();
        remove(pos);
    }
}

template <class Element>
void LinkedList<Element>::print() {
    NodeList<Element>* current = head->getNext();
    while (current != rear) {
        std::cout << current->getElement() << " ";
        current = current->getNext();
    }
    std::cout << std::endl;
}

// Explicit instantiation
template class LinkedList<int>;