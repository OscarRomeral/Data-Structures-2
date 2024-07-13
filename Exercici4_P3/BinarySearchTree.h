/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearchTree.h
 * Author: oscar
 *
 * Created on 16 / de maig / 2021, 13:40
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "BinaryTreeNode.h"

template <class K, class V>
class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree<K, V>& orig);
        virtual ~BinarySearchTree();

        bool isEmpty() const;
        int size() const;
        int height() const;
        
        BinaryTreeNode <K, V>* getRoot() const;

        BinaryTreeNode<K,V>* add(const K& k, const V& value);
        bool has(const K& k) const;
        const vector<V>& valuesOf(const K& k) const;

        void showKeysPreorder(const BinaryTreeNode<K,V>* n = nullptr) const;
        void showKeysInorder(const BinaryTreeNode<K,V>* n = nullptr) const;
        void showKeysPostorder(const BinaryTreeNode<K,V>* n = nullptr) const;

        bool equals(const BinarySearchTree<K, V>& other) const;
        vector<BinaryTreeNode<K, V>*> getLeafs() const;
    protected:
        BinaryTreeNode<K,V>* p_root;
        BinaryTreeNode<K,V>* find(const K& k) const;
    protected:
        int sizeInt(BinaryTreeNode<K,V>*) const; 
        bool hasInt(BinaryTreeNode<K,V>*, const K& k) const;
        bool equalsInt(const BinaryTreeNode<K,V>* node1, const BinaryTreeNode<K,V>* node2) const;
        void getLeafsInt(const BinaryTreeNode<K,V>* node1, vector <BinaryTreeNode<K, V> > &leafs) const;
        BinaryTreeNode<K, V>* findInt(const K& key, BinaryTreeNode<K,V>* node)const;
        void recalcularAlcada(BinaryTreeNode <K,V> *node);
};

template <class K, class V>
BinarySearchTree<K,V>::BinarySearchTree() {
    this->p_root = nullptr;
}

template <class K, class V>
BinarySearchTree<K,V>::BinarySearchTree(const BinarySearchTree& orig) {
    this->p_root = new BinaryTreeNode<K,V>(*orig.getRoot());
}

template <class K, class V>
bool BinarySearchTree<K,V>::isEmpty() const{
    if (this->p_root == nullptr){
        return true;
    }
    else return false;
}


template <class K, class V>
int BinarySearchTree<K,V>::size() const{
    return sizeInt(p_root);
    //utilitzem un mètode privat auxiliar per poder fer la recursivitat
}

template <class K, class V>
int BinarySearchTree<K,V>::sizeInt(BinaryTreeNode<K,V>* p) const{
    if(p == nullptr) return 0;
    else{
        return (sizeInt(p->getLeft()) + sizeInt(p->getRight()) + 1);
    }
}

template <class K, class V>
int BinarySearchTree<K,V>::height() const{
    if(isEmpty()){
        throw invalid_argument("El node arrel és nul");
        //Realitzem aquesta comprovació però podria no ser necessària ja que el mètode height
        //del BinaryTreeNode ja coprova si li passem un node nul
    }
    return p_root->getHeight();
}

template <class K, class V>
BinaryTreeNode <K, V>* BinarySearchTree<K,V>::getRoot() const{
    return this->p_root;
}

template <class K, class V>
BinaryTreeNode<K,V>* BinarySearchTree<K,V>::add(const K& k, const V& value){
    if(isEmpty()){
        p_root = new BinaryTreeNode<K,V>(k);
        p_root->addValue(value);
        cout << "inserta a l'arbre element: " << k << "\n";
        return p_root;
    }
    else{
        BinaryTreeNode<K,V> * node = p_root;
        BinaryTreeNode<K,V> * aux = nullptr;
        
        while(node != nullptr){
            aux = node;
            if(k > node->getKey()){
                node = node->getRight();
            }
            else if(k < node->getKey()){
                node = node->getLeft();
            }
            else{
                node = nullptr;
            }
        }
        BinaryTreeNode<K, V>* nounode;
        if(k > aux->getKey()){
            nounode = new BinaryTreeNode<K,V>(k);
            nounode->addValue(value);
            aux->setRight(nounode);
            nounode->setParent(aux);
        }
        else if (k < aux->getKey()){
            nounode = new BinaryTreeNode <K, V>(k);
            nounode->addValue(value);
            aux->setLeft(nounode);
            nounode->setParent(aux);
        }
        else{
            nounode = aux;
            nounode->addValue(value);
        }
        
        cout << "inserta a l'arbre element: " << k << "\n";
        recalcularAlcada(nounode);
        return nounode;
    
    }
    
}

template <class K, class V>
void BinarySearchTree<K,V>::recalcularAlcada(BinaryTreeNode <K,V> *node){
    while(node != nullptr){
        node->recalcularAlcada();
    }
}


template <class K, class V>
bool BinarySearchTree<K,V>::has(const K& k) const{
    if (isEmpty())
        throw invalid_argument ("Arbre buit\n");
    
    BinaryTreeNode <K, V>* node = p_root;
    return hasInt(node, k);
    //Cridem al mètode auxiliar
}

template <class K, class V>
bool BinarySearchTree<K,V>::hasInt(BinaryTreeNode<K,V>* r, const K& k) const{
    if(r == nullptr){
        return false;
    }
    if(r->getKey() == k){
        return true;
    }
    else if( k > r->getKey()){
        return hasInt(r->getRight(), k);
    }
    else return hasInt(r->getLeft(), k);
    //Ens anem movent per l'arbre seguint la comparació del key amb els nodes per saber si hi està o no
    //En cas de que s'arribi a nullptr, significa que no hem trobat cap node amb key k
}

template <class K, class V>
const vector<V>& BinarySearchTree<K,V>::valuesOf(const K& k) const{
    BinaryTreeNode<K,V> node = find(k);
    if (node == nullptr)
        throw invalid_argument("El node " + k + " no existeix\n");
    return node->getValues();
}

template <class K, class V>
void BinarySearchTree<K,V>::showKeysPreorder(const BinaryTreeNode<K,V>* n) const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit");
    }
    if( n != nullptr){
        cout << n->getKey() << ", ";
        if (n->getLeft() != nullptr)
            showKeysPreorder(n->getLeft());
        if (n ->getRight() != nullptr)
            showKeysPreorder(n->getRight());
    }
    else{
        showKeysPreorder(this->p_root);
    }
}

template <class K, class V>
void BinarySearchTree<K,V>::showKeysInorder(const BinaryTreeNode<K,V>* n) const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit");
    }
    if( n != nullptr){
        if (n->getLeft() != nullptr)
            showKeysInorder(n->getLeft());
        cout << n->getKey() << ", ";
        if (n ->getRight() != nullptr)
            showKeysInorder(n->getRight());
    }
    else{
        showKeysInorder(this->p_root);
    }
}

template <class K, class V>
void BinarySearchTree<K,V>::showKeysPostorder(const BinaryTreeNode<K,V>* n) const{
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit");
    }
    if( n != nullptr){
        if (n->getLeft() != nullptr)
            showKeysPostorder(n->getLeft());
        if (n ->getRight() != nullptr)
            showKeysPostorder(n->getRight());
        cout << n->getKey() << ", ";
    }
    else{
        showKeysPostorder(this->p_root);
    }
}

template <class K, class V>
bool BinarySearchTree<K,V>::equals(const BinarySearchTree<K, V>& other) const{
    if(this->size() != other.size()){
        return false;
    }
    else{
        return equalsInt(this->p_root, other.getRoot());
    }
}

template <class K, class V>
vector<BinaryTreeNode<K, V>*> BinarySearchTree<K,V>::getLeafs() const{
    if(isEmpty()){
        throw invalid_argument("L'arbre és buit, per tant no te fulles\n");
    }
    vector <BinaryTreeNode<K, V> > leafs;
    BinaryTreeNode<K,V> * node = p_root;
    getLeafsInt(node, leafs);
    
    return leafs;
}

template <class K, class V>
void BinarySearchTree<K,V>::getLeafsInt(const BinaryTreeNode<K,V>* node, vector <BinaryTreeNode<K, V> > &leafs) const{
    if(node->isLeaf()){
        leafs.push_back(node);
    }
    else{
        if(node->getLeft() != nullptr) leafs.push_back(node->getLeft());
        if(node->getRight() != nullptr) leafs.push_back(node->getRight());
    }
}

template <class K, class V>
BinaryTreeNode<K,V>* BinarySearchTree<K,V>::find(const K& k) const{
    BinaryTreeNode<K,V> * node = p_root;
    
    while (node != nullptr && k != node->getKey()){
        if(node->getKey() > k){
            node = node->getLeft();
        }
        else node = node->getRight();
    }
    return node;
    
}

template <class K, class V>
bool BinarySearchTree<K,V>::equalsInt(const BinaryTreeNode<K,V>* node1, const BinaryTreeNode<K,V>* node2) const{
    if(node1 == nullptr && node2 == nullptr){
        return true;
    }

    else if(*node1 == *node2 && node1 != nullptr && node2 != nullptr){
        return equalsInt(node1->getLeft(), node2->getLeft()) && equalsInt(node1->getRight(), node2->getRight());
    }
    return false;
}

template <class K, class V>
BinarySearchTree<K,V>::~BinarySearchTree() {
    cout << "Destruint arbre binari...\n";
    delete(p_root);
    cout << "Arbre binari destruit\n";
}

    
#endif /* BINARYSEARCHTREE_H */

