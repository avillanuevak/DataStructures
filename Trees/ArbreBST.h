/**
 * @author Albert Villanueva Kosoy 
*/

/**
 * 
 * Binary search tree
 * 
 * If the tree is well balanced the complexity of its operations is O(log2(n)).
 * Si l'arbre està ben equilibrat, la complexitat de les seves operacions és de O(log2 n).
 * If the tree is well balanced the complexity of its operations is O(log2(n)).
 * En canvi si no està equilibrat, la complexitat de les seves operacions és propera a O(n).
*/

#ifndef ARBREBST_H
#define ARBREBST_H
#include "NodeArbre.h"
#include <iostream>
#include <list>
using namespace std;

template <class CLAU, class VALOR>
class ArbreBST {
 public:
    ArbreBST(); // O(1) 
    ArbreBST(const ArbreBST<CLAU, VALOR>& orig); // O(n) Ha de copiar cada element
    virtual ~ArbreBST(); 
    bool buida() const; // O(1)
    int altura() const; 
    NodeArbre<CLAU,VALOR>* insereix(const CLAU& clau, const VALOR& value); // O(log 2 n), crida a cercar
    const VALOR& valorDe(const CLAU& clau) const; // O(log 2 n) també crida a la funcio cercar
    void imprimeixPreordre(const NodeArbre<CLAU,VALOR>* n = nullptr) const; // O(n), ha d'imprimir tot l'arbre
    void imprimeixInordre(const NodeArbre<CLAU,VALOR>* n = nullptr) const; // O(n)
    void imprimeixPostordre(const NodeArbre<CLAU,VALOR>* n = nullptr) const; // O(n)
    bool conteClau(const CLAU& clau) const; 
    void arbreMirall(); 
    list<NodeArbre<CLAU, VALOR>*> obteFullesArbre(bool esq) const;
protected:
    NodeArbre<CLAU,VALOR>* arrel;
    NodeArbre<CLAU,VALOR>* cercar(const CLAU& k) const; // Cerca fent servir cerca binària amb O(log2 n) si està equilibrat

private:
    int _mida;
 /* Mètodes auxiliars definiu aquí els que necessiteu */
    void obteFullesArbreAux(NodeArbre<CLAU, VALOR>* n, bool esq, list<NodeArbre<CLAU, VALOR>*>* llista)const;
    void arbreMirallAux(NodeArbre<CLAU,VALOR> *n); // O(n), ja que només ha de recorrer tot l'arbre
    NodeArbre<CLAU,VALOR> *cercarAux(NodeArbre<CLAU, VALOR> *node, const CLAU&K)const;
    void preordre(const NodeArbre<CLAU,VALOR>* n) const;
    void inordre(const NodeArbre<CLAU,VALOR>* n) const;
    void postordre(const NodeArbre<CLAU,VALOR>* n) const;
};

/**
 * Constructor senese paràmetres
*/
template <class CLAU, class VALOR>
ArbreBST<CLAU, VALOR>::ArbreBST(): _mida(0), arrel(nullptr){}

template <class CLAU, class VALOR>
ArbreBST<CLAU, VALOR>::ArbreBST(const ArbreBST<CLAU, VALOR>& orig){
    if (orig.arrel) {
        this->arrel = new NodeArbre<CLAU, VALOR>(*(orig.arrel));
    } else {
        this->arrel = nullptr;
    }
}

/**
 * Destructor
*/
template <class CLAU, class VALOR>
ArbreBST<CLAU, VALOR>::~ArbreBST(){
    delete arrel;
    cout << "\nArbre Esborrat\n" << endl;
}

/**
 * Mètode per veure si l'arbre està buit
 * @return bool si està buit
*/
template <class CLAU, class VALOR>
bool ArbreBST<CLAU, VALOR>::buida() const{
    return (this->arrel == nullptr); 
}

/**
 * Mètode que retorna l'altura de l'arbre, o que és el mateix, l'altura de l'arrel
 * @return int altura de l'arbre
*/
template <class CLAU, class VALOR>
int ArbreBST<CLAU, VALOR>::altura() const{
    return this->arrel->altura();
}

/**
 * Mètode que insereix una clau i un valor a l'arbre en forma de node en una posició ordenada per la clau
 * @return NodeArbre amb la clau i el valor dels paràmetres
*/
template <class CLAU, class VALOR>
NodeArbre<CLAU,VALOR>* ArbreBST<CLAU, VALOR>::insereix(const CLAU& clau, const VALOR& value){
    NodeArbre<CLAU, VALOR>* n = cercarAux(arrel, clau);
    _mida++;
    if (n == nullptr){
        arrel = new NodeArbre<CLAU, VALOR>(clau, value);
        return arrel;
    }
    else{
        if (clau < n->obteClau()){
            NodeArbre<CLAU, VALOR>* l = new NodeArbre<CLAU, VALOR>(clau, value);
            l->setParent(n);
            n->setLeft(l);
            return n->getLeft();
        }
        else {
            NodeArbre<CLAU, VALOR>* r = new NodeArbre<CLAU, VALOR>(clau, value);
            r->setParent(n);
            n->setRight(r);
            return n->getRight();
        }
    }
}
/**
 * Mètode que cerca un node en l'arbre amb l'identificador
 * @return NodeArbre el node amb la clau entrada
*/
template<class CLAU, class VALOR>
NodeArbre<CLAU,VALOR>* ArbreBST<CLAU, VALOR>::cercar(const CLAU& k) const{
    NodeArbre<CLAU, VALOR>* n = arrel;
    while (n != nullptr){
        if (n->obteClau() == k){
            return n;
        }
        if (n->obteClau() < k){
            n = n->getRight();
        }
        else if (n->obteClau() > k){
            n = n->getLeft();
        }
    }
    return nullptr;
}

/**
 * Mètode auxiliar al mètode de cerca de l'arbre
 * @return NodeArbre 
*/
template<class CLAU, class VALOR>
NodeArbre<CLAU, VALOR>* ArbreBST<CLAU, VALOR>::cercarAux(NodeArbre<CLAU,VALOR>* n, const CLAU& clau) const{
    if (n == nullptr || n->esExtern()){
        if (n != nullptr && clau == n->obteClau()) throw logic_error("Ja existeix un artista amb l'identificador\n");
        return n;
    }
    if (clau < n->obteClau()){
        return (n->getLeft() == nullptr) ? n : cercarAux(n->getLeft(), clau);
    }
    else if (clau > n->obteClau()){
        return (n->getRight() == nullptr) ? n: cercarAux(n->getRight(), clau);
    }
    else{
        throw logic_error("Ja existeix un artista amb l'identificador");
    }
}

/**
 * Mètode que retorna el valor d'un node amb la clau com a identificador
 * @return VALOR& amb la clau entrada
*/
template <class CLAU, class VALOR>
const VALOR& ArbreBST<CLAU, VALOR>::valorDe(const CLAU& clau) const{
    return cercar(clau)->obteValor();
}

/**
 * Mètodes per imprimir per pantalla l'arbre en forma de llista en preordre
*/
template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::imprimeixPreordre(const NodeArbre<CLAU,VALOR>* n) const{
    cout << "Llista preordre [ ";
    if (n != nullptr) preordre(n);
    else preordre(arrel);
    cout << "]";
}

template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::preordre(const NodeArbre<CLAU,VALOR>* n) const{
    cout << n->obteClau() << " ";
    if (n->teEsquerra()){
        preordre(n->getLeft());
    }
    if (n->teDreta()){
        preordre(n->getRight());
    }
}

/**
 * Mètodes per imprimir per pantalla l'arbre en forma de llista en inordre
*/
template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::imprimeixInordre(const NodeArbre<CLAU,VALOR>* n) const{
    cout << "Llista inordre [ ";
    if (n != nullptr) inordre(n);
    else inordre(arrel);
    cout << "]";
}

template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::inordre(const NodeArbre<CLAU,VALOR>* n) const{
    if (n->teEsquerra()){
        inordre(n->getLeft());
    }
    cout << n->obteClau() << " ";
    if (n->teDreta()){
        inordre(n->getRight());
    }
}

/**
 * Mètodes per imprimir per pantalla l'arbre en forma de llista en postordre
*/
template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::imprimeixPostordre(const NodeArbre<CLAU,VALOR>* n) const{
    cout << "Llista postordre [ ";
    if (n != nullptr) postordre(n);
    else postordre(arrel);
    cout << "]";
}

template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::postordre(const NodeArbre<CLAU,VALOR>* n) const{
    if (n->teEsquerra()){
        postordre(n->getLeft());
    }
    if (n->teDreta()){
        postordre(n->getRight());
    }
    cout << n->obteClau() << " ";
}

/**
 * Mètode que comprova si hi ha un node amb una clau com a paràmetre
 * @return bool si existeix un node amb aquesta clau
*/
template <class CLAU, class VALOR>
bool ArbreBST<CLAU, VALOR>::conteClau(const CLAU& clau) const{
    return (cercar(clau) == nullptr)? false : true;
}

/**
 * Mètodes que a partir de l'arbre actual el convertix en el seu mirall
*/
template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::arbreMirall(){
    (arrel != nullptr)? arbreMirallAux(arrel) : throw logic_error("Arbre buit\n");
}

template<class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::arbreMirallAux(NodeArbre<CLAU, VALOR>* n){
    if (n != nullptr){
        arbreMirallAux(n->getLeft());
        arbreMirallAux(n->getRight());
        NodeArbre<CLAU, VALOR>* temp = n->getRight();
        if (n->teDreta() && n->teEsquerra()){
            n->setRight(n->getLeft());
            n->setLeft(temp);
        }
        else if (!n->teDreta() && n->teEsquerra()){
            n->setRight(n->getLeft());
            delete n->getLeft();
        }
        else if (n->teDreta() && !n->teEsquerra()){
            n->setLeft(temp);
            delete n->getRight();
        }
    }
}

/**
 * Mètodes que retornen una llista amb totes les fulles de l'arbre esquerra o dret entrat un boleà
 * @return list<NodeArbre<CLAU, VALOR>*> amb les fulles de l'arbre del costat entrat
*/
template <class CLAU, class VALOR>
list<NodeArbre<CLAU, VALOR>*> ArbreBST<CLAU, VALOR>::obteFullesArbre(bool esq) const{
    list<NodeArbre<CLAU, VALOR>*> fulles;
    obteFullesArbreAux(arrel, esq, &fulles);
    return fulles;
}

template <class CLAU, class VALOR>
void ArbreBST<CLAU, VALOR>::obteFullesArbreAux(NodeArbre<CLAU, VALOR>* n, bool esq, list<NodeArbre<CLAU, VALOR>*>* llista) const{
    if (n == nullptr){
        llista->push_back(nullptr);
    }
    if (_mida == 1){
        llista->push_back(n);
    }
    else if (n->teEsquerra() && esq && n->getLeft()->esExtern()){
        llista->push_back(n->getLeft());
    }
    else if (n->teDreta() && !esq && n->getRight()->esExtern()){
        llista->push_back(n->getRight());
    }
    if (n->teEsquerra()){
        obteFullesArbreAux(n->getLeft(), esq, llista);
    }
    if (n->getRight()){
        obteFullesArbreAux(n->getRight(), esq, llista);
    }
}

#endif /* ARBREBST_H */