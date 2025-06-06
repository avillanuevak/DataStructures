/**
 * @author Albert Villanueva Kosoy 
 * 
 * ################################################
 * BINARY SEARCH TREE (BST). Defined with templates.
 * This class is used as a standard Binary Search Tree.
 * ################################################
 * 
 * ################################################
 * COMPLEXITY
 * 
 * Time and Space Complexity:
 * - If the tree is well balanced, all main operations (insert, search, delete) are O(log n) time and O(1) space per operation.
 * - If the tree is not balanced, the complexity can degrade to O(n) time per operation.
 * - Tree traversals (preorder, inorder, postorder) are O(n) time.
 * - The tree uses O(n) space for n nodes.
 * 
 * Si l'arbre està ben equilibrat, la complexitat de les seves operacions és de O(log n).
 * En canvi si no està equilibrat, la complexitat de les seves operacions és propera a O(n).
 * 
 * ################################################
 * ATRIBUTES
 * 
 * A BST node has a key (class CLAU) and a value (class VALOR).
 * It also has three pointers: parent, left child, and right child.
 * 
 * ################################################
 * 
 * ################################################
 * METHODS
 * 
 * CONSTRUCTORS  ##################################
 * 
 * BST : Default constructor for the BST class. Initializes the tree as empty.
 * 
 * BST(const BST&) : Copy constructor. Copies all nodes recursively.
 * 
 * ~BST : Destructor. Recursively deletes all nodes.
 * 
 * MODIFIERS  #####################################
 * 
 * insereix : Inserts a key and value into the BST.
 * arbreMirall : Converts the tree into its mirror.
 * 
 * CONSULTORS #####################################
 * 
 * buida : Returns true if the tree is empty.
 * altura : Returns the height of the tree.
 * valorDe : Returns the value associated with a key.
 * conteClau : Checks if a key exists in the tree.
 * imprimeixPreordre, imprimeixInordre, imprimeixPostordre : Print the tree in different orders.
 * obteFullesArbre : Returns a list of all leaves on the left or right side.
 * 
 * ################################################
 */

#ifndef BST_H
#define BST_H
#include "NodeTree.h"
#include <iostream>
#include <list>
using namespace std;

template <class CLAU, class VALOR>
class BST {
 public:
    BST(); // O(1) 
    BST(const BST<CLAU, VALOR>& orig); // O(n) Ha de copiar cada element
    virtual ~BST(); 
    bool buida() const; // O(1)
    int altura() const; 
    NodeTree<CLAU,VALOR>* insereix(const CLAU& clau, const VALOR& value); // O(log 2 n), crida a cercar
    const VALOR& valorDe(const CLAU& clau) const; // O(log 2 n) també crida a la funcio cercar
    void imprimeixPreordre(const NodeTree<CLAU,VALOR>* n = nullptr) const; // O(n), ha d'imprimir tot l'arbre
    void imprimeixInordre(const NodeTree<CLAU,VALOR>* n = nullptr) const; // O(n)
    void imprimeixPostordre(const NodeTree<CLAU,VALOR>* n = nullptr) const; // O(n)
    bool conteClau(const CLAU& clau) const; 
    void arbreMirall(); 
    list<NodeTree<CLAU, VALOR>*> obteFullesArbre(bool esq) const;
protected:
    NodeTree<CLAU,VALOR>* arrel;
    NodeTree<CLAU,VALOR>* cercar(const CLAU& k) const; // Cerca fent servir cerca binària amb O(log2 n) si està equilibrat

private:
    int _mida;
 /* Mètodes auxiliars definiu aquí els que necessiteu */
    void obteFullesArbreAux(NodeTree<CLAU, VALOR>* n, bool esq, list<NodeTree<CLAU, VALOR>*>* llista)const;
    void arbreMirallAux(NodeTree<CLAU,VALOR> *n); // O(n), ja que només ha de recorrer tot l'arbre
    NodeTree<CLAU,VALOR> *cercarAux(NodeTree<CLAU, VALOR> *node, const CLAU&K)const;
    void preordre(const NodeTree<CLAU,VALOR>* n) const;
    void inordre(const NodeTree<CLAU,VALOR>* n) const;
    void postordre(const NodeTree<CLAU,VALOR>* n) const;
};

/**
 * Constructor senese paràmetres
*/
template <class CLAU, class VALOR>
BST<CLAU, VALOR>::BST(): _mida(0), arrel(nullptr){}

template <class CLAU, class VALOR>
BST<CLAU, VALOR>::BST(const BST<CLAU, VALOR>& orig){
    if (orig.arrel) {
        this->arrel = new NodeTree<CLAU, VALOR>(*(orig.arrel));
    } else {
        this->arrel = nullptr;
    }
}

/**
 * Destructor
*/
template <class CLAU, class VALOR>
BST<CLAU, VALOR>::~BST(){
    delete arrel;
    cout << "\nArbre Esborrat\n" << endl;
}

/**
 * Mètode per veure si l'arbre està buit
 * @return bool si està buit
*/
template <class CLAU, class VALOR>
bool BST<CLAU, VALOR>::buida() const{
    return (this->arrel == nullptr); 
}

/**
 * Mètode que retorna l'altura de l'arbre, o que és el mateix, l'altura de l'arrel
 * @return int altura de l'arbre
*/
template <class CLAU, class VALOR>
int BST<CLAU, VALOR>::altura() const{
    return this->arrel->altura();
}

/**
 * Mètode que insereix una clau i un valor a l'arbre en forma de node en una posició ordenada per la clau
 * @return NodeTree amb la clau i el valor dels paràmetres
*/
template <class CLAU, class VALOR>
NodeTree<CLAU,VALOR>* BST<CLAU, VALOR>::insereix(const CLAU& clau, const VALOR& value){
    NodeTree<CLAU, VALOR>* n = cercarAux(arrel, clau);
    _mida++;
    if (n == nullptr){
        arrel = new NodeTree<CLAU, VALOR>(clau, value);
        return arrel;
    }
    else{
        if (clau < n->getKey()){
            NodeTree<CLAU, VALOR>* l = new NodeTree<CLAU, VALOR>(clau, value);
            l->setParent(n);
            n->setLeft(l);
            return n->getLeft();
        }
        else {
            NodeTree<CLAU, VALOR>* r = new NodeTree<CLAU, VALOR>(clau, value);
            r->setParent(n);
            n->setRight(r);
            return n->getRight();
        }
    }
}
/**
 * Mètode que cerca un node en l'arbre amb l'identificador
 * @return NodeTree el node amb la clau entrada
*/
template<class CLAU, class VALOR>
NodeTree<CLAU,VALOR>* BST<CLAU, VALOR>::cercar(const CLAU& k) const{
    NodeTree<CLAU, VALOR>* n = arrel;
    while (n != nullptr){
        if (n->getKey() == k){
            return n;
        }
        if (n->getKey() < k){
            n = n->getRight();
        }
        else if (n->getKey() > k){
            n = n->getLeft();
        }
    }
    return nullptr;
}

/**
 * Mètode auxiliar al mètode de cerca de l'arbre
 * @return NodeTree 
*/
template<class CLAU, class VALOR>
NodeTree<CLAU, VALOR>* BST<CLAU, VALOR>::cercarAux(NodeTree<CLAU,VALOR>* n, const CLAU& clau) const{
    if (n == nullptr || n->esExtern()){
        if (n != nullptr && clau == n->getKey()) throw logic_error("Ja existeix un artista amb l'identificador\n");
        return n;
    }
    if (clau < n->getKey()){
        return (n->getLeft() == nullptr) ? n : cercarAux(n->getLeft(), clau);
    }
    else if (clau > n->getKey()){
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
const VALOR& BST<CLAU, VALOR>::valorDe(const CLAU& clau) const{
    return cercar(clau)->getValue();
}

/**
 * Mètodes per imprimir per pantalla l'arbre en forma de llista en preordre
*/
template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::imprimeixPreordre(const NodeTree<CLAU,VALOR>* n) const{
    cout << "Llista preordre [ ";
    if (n != nullptr) preordre(n);
    else preordre(arrel);
    cout << "]";
}

template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::preordre(const NodeTree<CLAU,VALOR>* n) const{
    cout << n->getKey() << " ";
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
void BST<CLAU, VALOR>::imprimeixInordre(const NodeTree<CLAU,VALOR>* n) const{
    cout << "Llista inordre [ ";
    if (n != nullptr) inordre(n);
    else inordre(arrel);
    cout << "]";
}

template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::inordre(const NodeTree<CLAU,VALOR>* n) const{
    if (n->teEsquerra()){
        inordre(n->getLeft());
    }
    cout << n->getKey() << " ";
    if (n->teDreta()){
        inordre(n->getRight());
    }
}

/**
 * Mètodes per imprimir per pantalla l'arbre en forma de llista en postordre
*/
template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::imprimeixPostordre(const NodeTree<CLAU,VALOR>* n) const{
    cout << "Llista postordre [ ";
    if (n != nullptr) postordre(n);
    else postordre(arrel);
    cout << "]";
}

template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::postordre(const NodeTree<CLAU,VALOR>* n) const{
    if (n->teEsquerra()){
        postordre(n->getLeft());
    }
    if (n->teDreta()){
        postordre(n->getRight());
    }
    cout << n->getKey() << " ";
}

/**
 * Mètode que comprova si hi ha un node amb una clau com a paràmetre
 * @return bool si existeix un node amb aquesta clau
*/
template <class CLAU, class VALOR>
bool BST<CLAU, VALOR>::conteClau(const CLAU& clau) const{
    return (cercar(clau) == nullptr)? false : true;
}

/**
 * Mètodes que a partir de l'arbre actual el convertix en el seu mirall
*/
template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::arbreMirall(){
    (arrel != nullptr)? arbreMirallAux(arrel) : throw logic_error("Arbre buit\n");
}

template<class CLAU, class VALOR>
void BST<CLAU, VALOR>::arbreMirallAux(NodeTree<CLAU, VALOR>* n){
    if (n != nullptr){
        arbreMirallAux(n->getLeft());
        arbreMirallAux(n->getRight());
        NodeTree<CLAU, VALOR>* temp = n->getRight();
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
 * @return list<NodeTree<CLAU, VALOR>*> amb les fulles de l'arbre del costat entrat
*/
template <class CLAU, class VALOR>
list<NodeTree<CLAU, VALOR>*> BST<CLAU, VALOR>::obteFullesArbre(bool esq) const{
    list<NodeTree<CLAU, VALOR>*> fulles;
    obteFullesArbreAux(arrel, esq, &fulles);
    return fulles;
}

template <class CLAU, class VALOR>
void BST<CLAU, VALOR>::obteFullesArbreAux(NodeTree<CLAU, VALOR>* n, bool esq, list<NodeTree<CLAU, VALOR>*>* llista) const{
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

#endif /* BST_H */