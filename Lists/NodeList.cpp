#include "Node.h"

template <class Element>
NodeList<Element>::NodeList() : next(nullptr), previous(nullptr) {}

template <class Element>
NodeList<Element>::~NodeList() {}

template <class Element>
const Element& NodeList<Element>::getElement() const {
	    return element;
}

template <class Element>
NodeList<Element>* NodeList<Element>::getNext() const {
	    return next;
}

template <class Element>
void NodeList<Element>::setNext(NodeList<Element>* node) {
	    next = node;
}

template <class Element>
NodeList<Element>* NodeList<Element>::getPrevious() const {
	    return previous;
}

template <class Element>
void NodeList<Element>::setPrevious(NodeList<Element>* node) {
	    previous = node;
}

// Explicit instantiations
template class NodeList<int>;
