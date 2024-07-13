/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearchTree.h
 * Author: oscar
 *
 * Created on 27 / d’abril / 2021, 20:31
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
        void  mirall();
        void mirallAux(BinaryTreeNode * node);
        void mostraNodesNivell(int k);
        void mostraNodesNivell(BinaryTreeNode<K,V>* node, int k, int l);
    protected:
        BinaryTreeNode<K,V>* p_root;
        BinaryTreeNode<K,V>* find(const K& k) const;
    protected:
        int sizeInt(BinaryTreeNode<K,V>*) const; 
        bool hasInt(BinaryTreeNode<K,V>*, const K& k) const;
        bool equalsInt(const BinaryTreeNode<K,V>* node1, const BinaryTreeNode<K,V>* node2) const;
        void getLeafsInt(const BinaryTreeNode<K,V>* node1, vector <BinaryTreeNode<K, V> > &leafs) const;
        BinaryTreeNode<K, V>* findInt(const K& key, BinaryTreeNode<K,V>* node)const;
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
    return p_root->height();
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
            // Recorrem l'arbre fins a trobar el node on hi inserirem el nou node.
        }
        BinaryTreeNode<K, V>* nounode;
        //Diferenciem els casos en que inserim a la dreta, esquerra o que el node té la mateixa clau
        //En aquest cas únicament afegim el valor
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
        
        cout << "Inserta a l'arbre element: " << k << "\n";
        return nounode;
    
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
    //Retorna el vector de valors
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
    //Mostra primer el node pare, despres fill dret i finalment l'esquerre
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
    //Mostra primer el fill esquerre, després el pare i despres el dret
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
    //Mostra el fill esquerre, després el fill dret i després el pare
}

template <class K, class V>
bool BinarySearchTree<K,V>::equals(const BinarySearchTree<K, V>& other) const{
    if(this->size() != other.size()){
        return false;
    }
    else{
        return equalsInt(this->p_root, other.getRoot());
    }
    //crida al mètode auxiliar 
}

template <class K, class V>
vector<BinaryTreeNode<K, V>*> BinarySearchTree<K,V>::getLeafs() const{
    if(isEmpty()){
        throw invalid_argument("L'arbre és buit, per tant no te fulles\n");
    }
    vector <BinaryTreeNode<K, V> > leafs;
    BinaryTreeNode<K,V> * node = p_root;
    getLeafsInt(node, leafs);
    //Crida al mètode auxiliar
    return leafs;
}

template <class K, class V>
void BinarySearchTree<K,V>::getLeafsInt(const BinaryTreeNode<K,V>* node, vector <BinaryTreeNode<K, V> > &leafs) const{
    if(node->isLeaf()){
        leafs.push_back(node);
    }
    else{
        if(node->getLeft() != nullptr)
            getLeafsInt(node->getLeft(), leafs);
        if(node->getRight() != nullptr)
            getLeafsInt(node->getRight(), leafs);
    }
    //Retornem un vector amb les fulles de l'arbre, va recorrent i en cas de que sigui fulla, s'afegeix al vector 
}

template <class K, class V>
void BinarySearchTree<K,V>:: mirall(){
    if(isEmpty()){
        throw invalid_argument("Arbre buit");
    }
    BinaryTreeNode * node = p_root;
    mirallAux(node);
}

template <class K, class V>
void BinarySearchTree<K,V>::mirallAux(BinaryTreeNode * node){
    if(node != nullptr){
        if(node->getLeft() != nullptr){
            mirallAux(node->getLeft());
        }
        if(node->getRight() != nullptr){
            mirallAux(node->getRight());
        }
        BinaryTreeNode * aux = node->getLeft();
        node->setLeft(node->getRight());
        node->setRight(aux);
    }
    else return;
       
}

template <class K, class V>
void BinarySearchTree<K,V>:: mostraNodesNivell(int k){
    BinaryTreeNode * node = p_root;
    int l = 0;
    mostraNodesNivell(node, k, l);
}

template <class K, class V>
void BinarySearchTree<K,V>:: mostraNodesNivell(BinaryTreeNode<K,V>* node, int k, int l){
    if (l == k){
        cout << node->getKey();
    }
    else{
        l++;
        if(node->getLeft() != nullptr) mostraNodesNivell(node, k, l);
        if(node->getRight() != nullptr) mostraNodesNivell(node, k, l);
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
    //Retorna nul o el node si l'ha trobat, comparant la k amb la key de cada node
    
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
    // En cas que un d'ells sigui nul i l'altre no, false. Si els dos són no nuls comparem node a node
}






template <class K, class V>
BinarySearchTree<K,V>::~BinarySearchTree() {
    cout << "Destruint arbre binari...\n";
    delete(p_root);
    cout << "Arbre binari destruit\n";
}

    
#endif /* BINARYSEARCHTREE_H */

