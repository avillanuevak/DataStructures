/**
 * @author Albert Villanueva Kosoy Grup C
*/

/***
 * ARBRE AVL
 * 
 * El cost computacional d'insereixAVL és O(log2 n) ja que crida al mètode cercar de Arbre BST. 
 * Com que al balencejar, està perfectament equilibrat, la complexitat de les seves operacions (inserir, cercar
 * i eliminar) és de O(log2 n).
 * 
 * 
 * Diferències entre AVL i BST
 * 
 * Els arbres AVL i BST són casi idèntics. Difereixen únicament en l'equilibri que comporta l'arbre
 * AVL, que permet tenir una complexitat menor que el BST i ser més eficient en quasi totes les situacions.
 * 
 * En quan a mètodes, l'arbre AVL té els mètodes de l'arbre BST més els necessaris per fer el balanceig:
 * InsereixAVL, balanceig, actualitza arbre, rotació dreta simple, rotació esquerra simple, rotació dreta
 * doble i rotació esquerra doble.
*/

#ifndef ARBREAVL_H
#define ARBREAVL_H
#include "ArbreBST.h"
#include "NodeArbre.h"

template <class K, class V>
class ArbreAVL: public ArbreBST<K, V> {
    public:
    ArbreAVL(); // O(1)
    NodeArbre<K,V>* insereixAVL(const K& clau, const V& value);

    private:
        int balanceig(NodeArbre<K, V>* n);
        void actualitzaArbre(NodeArbre<K, V>* n);
        void dretaSimple(NodeArbre<K, V>*n);
        void esquerraSimple(NodeArbre<K, V>*n);
        void dretaDoble(NodeArbre<K, V>*n);
        void esquerraDoble(NodeArbre<K, V>*n);
        
};
/**
 * Constructor sense parametres de la classe ArbreAVL
*/
template <class K, class V>
ArbreAVL<K, V>::ArbreAVL():ArbreBST<K, V>(){}

/**
 * Balanceig: altura del node esquerra - altura del node dreta
 * @return int balanç en el node entrat
*/
template <class K, class V>
int ArbreAVL<K, V>::balanceig(NodeArbre<K, V>* n){
    int b = (n->teEsquerra()? n->getLeft()->altura():0) - (n->teDreta()? n->getRight()->altura():0);
    return b;
}

/**
 * Canvi d'inserció per fer els balancejos
 * @return NodeArbre<K,V> node inserit
*/
template <class K, class V>
NodeArbre<K,V>* ArbreAVL<K, V>::insereixAVL(const K& clau, const V& value){
    NodeArbre<K, V>* t =  this->insereix(clau, value);
    actualitzaArbre(t);
    return t; 
}
/**
 * Actualitza la distribució de l'arbre balancejant-lo
*/
template <class K, class V>
void ArbreAVL<K, V>::actualitzaArbre(NodeArbre<K, V>*n){
    int b = balanceig(n);

    if (b > 1 || b < -1){
        if (b > 1){
            if (balanceig(n->getLeft()) > 0) dretaSimple(n);
            else if (balanceig(n->getLeft()) < 0) esquerraDoble(n);
        }
        if (b < -1){
            if (balanceig(n->getRight()) < 0) esquerraSimple(n);
            else if (balanceig(n->getRight()) > 0) dretaDoble(n);
        }
    }
    else{
        if (n->getParent()){
            actualitzaArbre(n->getParent());
        }
    }
}

/**
 * Rotacions
*/
template <class K, class V>
void ArbreAVL<K, V>::dretaSimple(NodeArbre<K, V>*n){
    NodeArbre<K, V> *p = n->getParent();
    NodeArbre<K, V> *t = n->getLeft();

    n->setLeft(t->getRight());
    if(t->getRight()) t->getRight()->setParent(n);
    n->setParent(t);
    t->setRight(n);
    t->setParent(p);
    if(p == nullptr) this->arrel = t;
    else if(p->teDreta() && p->getRight() != n) p->setLeft(t); 
    else p->setRight(t); 
}

template <class K, class V>
void ArbreAVL<K, V>::esquerraSimple(NodeArbre<K, V>*n){
    NodeArbre<K,V> *p=n->getParent();
    NodeArbre<K,V> *t=n->getRight();

    n->setRight(t->getLeft());
    if(t->getLeft()) t->getLeft()->setParent(n);
    n->setParent(t);
    t->setLeft(n);
    t->setParent(p);
    if(p == nullptr) this->arrel = t;
    else if(p->teEsquerra() && p->getLeft() != n) p->setRight(t);
    else p->setLeft(t);
}

template <class K, class V>
void ArbreAVL<K, V>::dretaDoble(NodeArbre<K, V>*n){
    dretaSimple(n->getRight());
    esquerraSimple(n);
}

template <class K, class V>
void ArbreAVL<K, V>::esquerraDoble(NodeArbre<K, V>*n){
    esquerraSimple(n->getLeft());
    dretaSimple(n);
}

#endif /*ARBREAVL_H*/