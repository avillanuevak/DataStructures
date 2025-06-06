#ifndef NODE_H
#define NODE_H

template <class Element>

class NodeList{
    public:
        NodeList();
        ~NodeList();

        const Element& getElement() const;

        NodeList<Element>* getNext() const;
        void setNext(NodeList<Element>* node);

        NodeList<Element>* getPrevious() const;
        void setPrevious(NodeList<Element>* node);

        void setElement(const Element& element) { this->element = element; } // Add this setter

    private:
        Element element;
        NodeList<Element>* next;
        NodeList<Element>* previous;
};

#endif