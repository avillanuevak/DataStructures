/**
 * @author Albert Villanueva Kosoy 
 * 
 * ################################################
 * A TreeNode. Defined with templates.
 * This class is used in Binary Search Tree and Auto-Balancing Binary Tree.
 * ################################################
 * 
 * ################################################
 * ATRIBUTES
 * 
 * A tree node has a key called class KEY and a value called class VALUE. 
 * It also has three pointers of the same NodeTree type; parent, left child and right child.
 * 
 * ################################################
 * 
 * ################################################
 * METHODS
 * 
 * CONSTRUCTORS  ##################################
 * 
 * NodeTree : This method is a constructor for the NodeTree class. 
 * This constructor takes in two parameters; a KEY parameter and a VALUE parameter. They are admitted through reference (&var) and are const.
 * This constructor sets the value of the key to the one entered and the value of the VALUE to the value entered.
 * The left, right and parent pointers are set to nullptr.
 * 
 * NodeTree : This method is a copy constructor for the NodeTree class.
 * This constructor takes in one parameter 
 * 
 * 
*/

#ifndef NodeTree_H
#define NodeTree_H
#include <iostream>
using namespace std;

template <class KEY, class VALUE >
class NodeTree {
public:
    /* Constructors */
    NodeTree(const KEY& key, const VALUE& v); //Constructor O(1)
    NodeTree(const NodeTree<KEY,VALUE>& orig); // Constructor copia O(n)
    virtual ~NodeTree(); //Destructor O(n)
    /* Modifiers */

    void setParent(NodeTree<KEY, VALUE>* parent);
    void setLeft(NodeTree<KEY, VALUE>* left);
    void setRight(NodeTree<KEY, VALUE>* right);

    /* Consultors */
    const KEY& getKey() const;
    const VALUE& getValue() const;

    NodeTree<KEY, VALUE>* getParent()const;
    NodeTree<KEY, VALUE>* getRight()const;
    NodeTree<KEY, VALUE>* getLeft()const;

    /* Operacions */
    bool esArrel() const;
    bool teEsquerra() const;
    bool teDreta() const;
    bool esExtern() const;
    void insereixVALUE(const VALUE & v);
    int altura() const;
    bool operator==(const NodeTree<KEY,VALUE>& node) const;

private:
    KEY key;
    VALUE value;
    NodeTree<KEY, VALUE>* left;
    NodeTree<KEY, VALUE>* right;
    NodeTree<KEY, VALUE>* parent;
};

/**
 * Constructors i destructors
*/
template <class KEY, class VALUE>
NodeTree <KEY, VALUE>::NodeTree(const KEY& key, const VALUE& v){
            this->key = key; 
            this->value = v; 
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }

template <class KEY, class VALUE>
NodeTree<KEY,VALUE>::NodeTree(const NodeTree<KEY,VALUE>& orig){
    this->key = orig.key;
    this->value = orig.value;
    this->parent = orig.parent;
    this->left = nullptr;
    this->right = nullptr;

    if(orig.teEsquerra()){
        left = new NodeTree<KEY,VALUE>(*orig.getLeft());
    }
    if(orig.teDreta()){
        right = new NodeTree<KEY,VALUE>(*orig.getRight());
    }
}

template<class KEY, class VALUE>
NodeTree<KEY, VALUE>::~NodeTree(){
    if(this->teEsquerra()){
        delete this->left;
    }
    if (this->teDreta())
    {
        delete this->right;
    }
}

/**
 * Consultors i modificadors
*/
template<class KEY, class VALUE>
void NodeTree<KEY, VALUE>::setParent(NodeTree<KEY, VALUE>* parent){
    this->parent = parent;
}
/**
 * Insereix un VALUE entrat com a VALUE del node
*/
template<class KEY, class VALUE>
void NodeTree<KEY, VALUE>::insereixVALUE(const VALUE & v){
    this->value = v;
}

template<class KEY, class VALUE>
void NodeTree<KEY, VALUE>::setLeft(NodeTree<KEY, VALUE>* left){
    this->left = left;
}

template<class KEY, class VALUE>
void NodeTree<KEY, VALUE>::setRight(NodeTree<KEY, VALUE>* right){
    this->right = right;
}

template<class KEY, class VALUE>
NodeTree<KEY, VALUE>* NodeTree<KEY, VALUE>::getParent()const {
    return this->parent;
    }

template<class KEY, class VALUE>
NodeTree<KEY, VALUE>* NodeTree<KEY, VALUE>::getLeft()const {
    return this->left;
    }

template<class KEY, class VALUE>
NodeTree<KEY, VALUE>* NodeTree<KEY, VALUE>::getRight()const {
    return this->right;
    }

template<class KEY, class VALUE>
const KEY& NodeTree<KEY, VALUE>::getKey() const{
    return this->key;
}

template<class KEY, class VALUE>
const VALUE& NodeTree<KEY, VALUE>::getValue() const{
    return this->value;
}

/**
 * Mètode per veure si el node és arrel
 * @return bool si el node és arrel o no
*/
template<class KEY, class VALUE>
bool NodeTree<KEY, VALUE>::esArrel() const{
    return this->parent == nullptr;
}

/**
 * Mètode per veure si el node té esquerra o no
 * @return bool si el node té esquerra o no
*/
template<class KEY, class VALUE>
bool NodeTree<KEY, VALUE>::teEsquerra() const{
    return this->left != nullptr;
}

/**
 * Mètode per veure si el node té dreta o no
 * @return bool si el node té dreta o no
*/
template<class KEY, class VALUE>
bool NodeTree<KEY, VALUE>::teDreta() const{
    return this->right != nullptr;
}

/**
 * Mètode per veure si el node és extern o no
 * @return bool si el node és extern o no
*/
template<class KEY, class VALUE>
bool NodeTree<KEY, VALUE>::esExtern() const{
    return !teEsquerra() && !teDreta();
}

/**
 * Mètode per calcular l'altura del node
 * @return int l'altura del node
*/
template<class KEY, class VALUE>
int NodeTree<KEY, VALUE>::altura() const{
   int altura = 0;
    if (esExtern()) altura = 1;
    else{
        int l = 0, r = 0;
        if (teEsquerra()) l = left->altura();
        if (teDreta()) r = right->altura();

        altura = 1 + max(l, r);
    }
    return altura;
}

/**
 * Sobrecàrrega del operador '==' per comprovar l'igualtat de dos nodes
 * @return bool true si els nodes són iguals
*/
template<class KEY, class VALUE>
bool NodeTree<KEY, VALUE>::operator==(const NodeTree<KEY,VALUE>& node) const{
    return ((this->key == node.getKey()) && (this->value == node.getValue()));
}

#endif