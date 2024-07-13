/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTreeNode.h
 * Author: oscar
 *
 * Created on 10 / de maig / 2021, 10:24
 */

#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
#include <vector>
#include <stdexcept>
using namespace std;

template <class K, class V>
class BinaryTreeNode {
    public:
        BinaryTreeNode(const K& key);
        BinaryTreeNode(const BinaryTreeNode<K,V>& orig);
        virtual ~BinaryTreeNode();

        /* Modificadors */
        // Declareu-hi aquí els modificadors (setters) dels atributs que manquen

        /* Consultors */
        const K& getKey() const;
        const vector<V>& getValues() const;
        BinaryTreeNode<K,V> * getParent() const;
        BinaryTreeNode<K,V> * getLeft() const;
        BinaryTreeNode<K,V> * getRight() const;
        void setParent(BinaryTreeNode<K,V> * parent);
        void setRight(BinaryTreeNode<K,V> * right); //Afegim aquests sets per puguer afegir nodes a l'arbre
        void setLeft(BinaryTreeNode<K,V> * left); //Ja que el getLeft o getRight retornen un const que no podem modificar
        /* Operacions */
        bool isRoot() const;
        bool hasLeft() const;
        bool hasRight() const;
        bool isLeaf() const;

        void addValue(const V& v);
        int depth() const;
        int height() const; // uses auxiliary attribute
        bool operator==(const BinaryTreeNode<K,V>& node) const;
    private:
        K key;
        vector <V> values;
        BinaryTreeNode * parent;
        BinaryTreeNode * left;
        BinaryTreeNode * right;  
        int heightInt(BinaryTreeNode<K,V> * node) const;
        int depthInt(BinaryTreeNode<K,V> * node) const;
        
};

template <class K, class V>
BinaryTreeNode<K, V>::BinaryTreeNode(const K& key) {
    this->key = key;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <class K, class V>
BinaryTreeNode<K, V>::BinaryTreeNode(const BinaryTreeNode<K,V>& orig){
    this->key = orig.getKey();
    this->values = orig.getValues();
    if(orig.left != nullptr){
        this->left = new BinaryTreeNode<K,V>(*orig.getLeft());
        this->left->setParent(this);
    }
    if(orig.right != nullptr){
        this->right = new BinaryTreeNode<K,V>(*orig.getRight());
        this->right->setParent(this);
    }
    //No cal fer copa del parent, ja que en el cas de que el node sigui arrel
    //no en tindra, i si no és arrel ja haurem fet el setParent() al copiar el seu ascendent.
}

template <class K, class V>
const K& BinaryTreeNode<K, V>::getKey() const{
    return this->key;
}

template <class K, class V>
const vector<V>& BinaryTreeNode<K, V>::getValues() const{
    return this->values;
}

template <class K, class V>
BinaryTreeNode<K, V> * BinaryTreeNode<K, V>::getParent() const{
    return this->parent;
}

template <class K, class V>
BinaryTreeNode<K, V> * BinaryTreeNode<K, V>::getLeft() const{
    return this->left;
}

template <class K, class V>
BinaryTreeNode<K, V> * BinaryTreeNode<K, V>::getRight() const{
    return this->right;
}

template <class K, class V>
void BinaryTreeNode<K, V>::setParent(BinaryTreeNode<K,V> * parent){
    this->parent = parent;
}

template <class K, class V>
void BinaryTreeNode<K, V>::setLeft(BinaryTreeNode<K,V> * left){
    this->left = left;
}

template <class K, class V>
void BinaryTreeNode<K, V>::setRight(BinaryTreeNode<K,V> * right){
    this->right = right;
}

template <class K, class V>
bool BinaryTreeNode<K, V>::isRoot() const{
    if(getParent() == nullptr){
        return true;
    }
    else return false;
}

template <class K, class V>
bool BinaryTreeNode<K, V>::hasLeft() const{
    if(left == nullptr){
        return false;
    }
    else return true;
}

template <class K, class V>
bool BinaryTreeNode<K, V>::hasRight() const{
    if(right == nullptr){
        return false;
    }
    else return true;
}

template <class K, class V>
bool BinaryTreeNode<K, V>::isLeaf() const{
    if(!hasRight() && !hasLeft()){
        return true;
    }
    else return false;
}

template <class K, class V>
void BinaryTreeNode<K, V>::addValue(const V& v){
    values.push_back(v);
}

template <class K, class V>
int BinaryTreeNode<K, V>::depth() const{
    return depthInt(this);
}

template <class K, class V>
int BinaryTreeNode<K, V>::depthInt(BinaryTreeNode<K,V> * node) const{
    if(isRoot()){
        return 0;
    }
    else{
        return 1 + depth(getParent());
    }
}

template <class K, class V>
int BinaryTreeNode<K, V>::height() const{
    int max;
    if(this == nullptr){
        throw invalid_argument("El node del que es vol calcular la altura és nul");
        //Pel cas en que el node inicial del que volem trobar height sigui nullptr.
    }
    return heightInt(this);
    
}

template <class K, class V>
int BinaryTreeNode<K, V>::heightInt(BinaryTreeNode<K,V> * node) const{
    if(isLeaf()){
        return 1;
    }
    else{
        if(getLeft() != nullptr && getRight() != nullptr){
            return max(heightInt(getLeft()), heightInt(getRight())) + 1;
        }
        else if (getLeft() == nullptr) return heightInt(getRight()) + 1; 
        else return heightInt(getLeft()) + 1;
    }
}

template <class K, class V>
bool BinaryTreeNode<K, V>::operator==(const BinaryTreeNode<K,V>& node) const{
    if(getKey() == node.getKey() && getValues() == node.getValues()){
        return true;
    }
    else return false;
}

template <class K, class V>
BinaryTreeNode<K, V>::~BinaryTreeNode() {
    delete left;
    delete right;
    cout << "Node " << getKey() << " eliminat\n";
}



#endif /* BINARYTREENODE_H */