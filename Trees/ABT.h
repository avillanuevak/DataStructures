/**
 * @author Albert Villanueva Kosoy Grup C
 * 
 * ################################################
 * AVL Tree (Arbre AVL). Defined with templates.
 * This class is used as a self-balancing Binary Search Tree.
 * ################################################
 * 
 * ################################################
 * COMPLEXITY
 * 
 * Time and Space Complexity:
 * - Insertion (insereixAVL), search, and removal: O(log n) time and O(1) space per operation, since the tree remains balanced.
 * - Rotations and balancing operations: O(1) time per rotation.
 * - The tree uses O(n) space for n nodes.
 * 
 * AVL trees are self-balancing binary search trees. All operations are efficient due to automatic balancing after insertions and deletions.
 * 
 * Differences between AVL and BST:
 * AVL and BST trees are almost identical. The only difference is the balancing in AVL, which ensures better performance in most cases.
 * The AVL tree has all BST methods plus those needed for balancing: insereixAVL, balanceig, actualitzaArbre, dretaSimple, esquerraSimple, dretaDoble, esquerraDoble.
 * 
 * ################################################
 * ATRIBUTES
 * 
 * An AVL tree node has a key (class K) and a value (class V).
 * It inherits the structure and pointers from the BST node: parent, left child, and right child.
 * 
 * ################################################
 * 
 * ################################################
 * METHODS
 * 
 * CONSTRUCTORS  ##################################
 * 
 * ArbreAVL : Default constructor for the AVL tree class. Initializes the tree as empty.
 * 
 * insereixAVL : Inserts a key and value into the AVL tree and rebalances if necessary.
 * 
 * ~ArbreAVL : Destructor inherited from BST, recursively deletes all nodes.
 * 
 * MODIFIERS  #####################################
 * 
 * dretaSimple, esquerraSimple, dretaDoble, esquerraDoble : Perform rotations to maintain AVL balance.
 * actualitzaArbre : Updates and rebalances the tree after insertion.
 * 
 * CONSULTORS #####################################
 * 
 * balanceig : Returns the balance factor of a node.
 * 
 * ################################################
 */

// Complexity summary for implementation:
// - All AVL operations (insert, search, delete) are O(log n) due to balancing.
// - Rotations are O(1).
// - Space is O(n).

#ifndef ARBREAVL_H
#define ARBREAVL_H
#include "BST.h"
#include "NodeTree.h"

template <class K, class V>
class ABT: public BST<K, V> {
public:
    ABT(); // O(1)
    NodeTree<K,V>* insereixAVL(const K& clau, const V& value);

private:
    int balanceig(NodeTree<K, V>* n);
    void actualitzaArbre(NodeTree<K, V>* n);
    void dretaSimple(NodeTree<K, V>*n);
    void esquerraSimple(NodeTree<K, V>*n);
    void dretaDoble(NodeTree<K, V>*n);
    void esquerraDoble(NodeTree<K, V>*n);
};

// Implementation

template <class K, class V>
ABT<K, V>::ABT() : BST<K, V>() {}

template <class K, class V>
int ABT<K, V>::balanceig(NodeTree<K, V>* n) {
    int b = (n->teEsquerra() ? n->getLeft()->altura() : 0) - (n->teDreta() ? n->getRight()->altura() : 0);
    return b;
}

template <class K, class V>
NodeTree<K,V>* ABT<K, V>::insereixAVL(const K& clau, const V& value) {
    NodeTree<K, V>* t = this->insereix(clau, value);
    actualitzaArbre(t);
    return t;
}

template <class K, class V>
void ABT<K, V>::actualitzaArbre(NodeTree<K, V>*n) {
    int b = balanceig(n);

    if (b > 1 || b < -1) {
        if (b > 1) {
            if (balanceig(n->getLeft()) > 0) dretaSimple(n);
            else if (balanceig(n->getLeft()) < 0) esquerraDoble(n);
        }
        if (b < -1) {
            if (balanceig(n->getRight()) < 0) esquerraSimple(n);
            else if (balanceig(n->getRight()) > 0) dretaDoble(n);
        }
    } else {
        if (n->getParent()) {
            actualitzaArbre(n->getParent());
        }
    }
}

template <class K, class V>
void ABT<K, V>::dretaSimple(NodeTree<K, V>*n) {
    NodeTree<K, V> *p = n->getParent();
    NodeTree<K, V> *t = n->getLeft();

    n->setLeft(t->getRight());
    if (t->getRight()) t->getRight()->setParent(n);
    n->setParent(t);
    t->setRight(n);
    t->setParent(p);
    if (p == nullptr) this->arrel = t;
    else if (p->teDreta() && p->getRight() != n) p->setLeft(t);
    else p->setRight(t);
}

template <class K, class V>
void ABT<K, V>::esquerraSimple(NodeTree<K, V>*n) {
    NodeTree<K,V> *p = n->getParent();
    NodeTree<K,V> *t = n->getRight();

    n->setRight(t->getLeft());
    if (t->getLeft()) t->getLeft()->setParent(n);
    n->setParent(t);
    t->setLeft(n);
    t->setParent(p);
    if (p == nullptr) this->arrel = t;
    else if (p->teEsquerra() && p->getLeft() != n) p->setRight(t);
    else p->setLeft(t);
}

template <class K, class V>
void ABT<K, V>::dretaDoble(NodeTree<K, V>*n) {
    dretaSimple(n->getRight());
    esquerraSimple(n);
}

template <class K, class V>
void ABT<K, V>::esquerraDoble(NodeTree<K, V>*n) {
    esquerraSimple(n->getLeft());
    dretaSimple(n);
}

#endif /*ARBREAVL_H*/