#include "Position.h"

template <class Element>
Position<Element>::Position(NodeList<Element>* node) : node(node) {}

template <class Element>
Position<Element>::~Position() {}

template <class Element>
Position<Element> Position<Element>::next() const {
    return Position<Element>(node->getNext());
}

template <class Element>
Position<Element> Position<Element>::previous() const {
    return Position<Element>(node->getPrevious());
}

template <class Element>
const Element& Position<Element>::element() const {
    return node->getElement();
}

template <class Element>
void Position<Element>::setPrevious(NodeList<Element>* node) {
    this->node->setPrevious(node);
}

template <class Element>
void Position<Element>::setNext(NodeList<Element>* node) {
    this->node->setNext(node);
}

template <class Element>
Position<Element> Position<Element>::operator++() const {
    return next();
}

template <class Element>
Position<Element> Position<Element>::operator--() const {
    return previous();
}

template <class Element>
bool Position<Element>::operator!=(const Position& other) const {
    return node != other.node;
}

template <class Element>
const Element& Position<Element>::operator*() const {
    return node->getElement();
}

// Explicit instantiation
template class Position<int>;