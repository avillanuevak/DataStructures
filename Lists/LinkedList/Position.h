#include "Node.h"

#ifndef POSITION_H
#define POSITION_H

template <class Element> class LinkedList;

template <class Element>
class Position{
    public:
    Position(NodeList<Element>* node);
    ~Position();

    Position<Element> next() const;
    Position<Element> previous() const;
    const Element& element() const;

    void setPrevious(NodeList<Element>* node);
    void setNext(NodeList<Element>* node);

    Position<Element> operator++() const;
    Position<Element> operator--() const;
    bool operator!=(const Position& other) const;
    const Element& operator*() const;

    private:
        NodeList<Element>* node;
        
    friend class LinkedList<Element>;
};
#endif