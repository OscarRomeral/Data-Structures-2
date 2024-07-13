/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.h
 * Author: oscar
 *
 * Created on 16 / de maig / 2021, 13:39
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include "Transaction.h"
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

template <class K, class V>
class AVLTree : public BinarySearchTree<K, V>{
public:
    AVLTree();
    AVLTree(const AVLTree<K, V>& orig);
    void afegirBalancejar(const K& k, const V& value);
    void rotacioEsq(BinaryTreeNode<K, V> *node);
    void rotacioDre(BinaryTreeNode<K, V> *node);
    BinaryTreeNode <K, V>* recalcularBF(BinaryTreeNode<K, V> *node);
    virtual ~AVLTree();
private:

};

template <class K, class V>
AVLTree<K, V>::AVLTree(): BinarySearchTree<K,V>() {
}

template <class K, class V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V>& orig): BinarySearchTree<K,V>(orig){
}



template <class K, class V>
void AVLTree<K, V>::afegirBalancejar(const K& k, const V& value){
    BinaryTreeNode<K,V> * afegit = this->add(k,value);
    BinaryTreeNode<K,V> * alpha = recalcularBF(afegit);
    
    this->recalcularAlcada(afegit);
    if(alpha != nullptr){
        if(alpha->getKey() > afegit->getKey()){
            if(alpha->getLeft()->getKey() < afegit->getKey()){
                rotacioEsq(alpha);
                rotacioDre(alpha->getParent()->getParent());
                //this->recalcularAlcada(alpha);
                //this->recalcularAlcada(alpha->getLeft());
                //this->recalcularAlcada(alpha->getLeft()->getRight());
            }
            else rotacioDre(alpha);
            
        }
        else{
            if(alpha->getRight()->getKey() > afegit->getKey()){
                rotacioDre(alpha);
                rotacioEsq(alpha->getParent()->getParent());
            }
            else{
                rotacioEsq(alpha);
            }
        }
    }
    
    
     
}





template <class K, class V>
void AVLTree<K, V>::rotacioEsq(BinaryTreeNode<K, V> *node){
   
    if(node->getRight()->getLeft() != nullptr){
        node->setRight(node->getRight()->getLeft());
        node->getRight()->getParent()->setLeft(node);
    
    
        if(node->getParent() != nullptr) {
            if(node->getKey() < node->getParent()->getKey()){
                node->getParent()->setLeft(node->getRight()->getParent());
                node->getRight()->getParent()->setParent(node->getParent());
                node->setParent(node->getRight()->getParent());
                node->getRight()->setParent(node);
            }
            else{
               node->getParent()->setRight(node->getRight()->getParent());
               node->getRight()->getParent()->setParent(node->getParent());
               node->setParent(node->getRight()->getParent());
               node->getRight()->setParent(node);
            }
        }
        else{
            node->getRight()->getParent()->setParent(nullptr);
            node->getRight()->getParent()->setLeft(node);
            node->setParent(node->getRight()->getParent());
            node->getRight()->setParent(node);
        }
    }
    else{
        BinaryTreeNode<K,V> * aux = node->getRight();
        node->getRight()->setLeft(node);
        if(node->getKey() < node->getParent()->getKey()){
            node->getRight()->setParent(node->getParent());
            node->getParent()->setLeft(node->getRight());
            node->setParent(node->getRight());
            node->setRight(nullptr);
        }
        else{
            node->getRight()->setParent(node->getParent());
            node->getParent()->setRight(node->getRight());
            node->setParent(node->getRight());
            node->setRight(nullptr);
        }
    }
    
    
}


template <class K, class V>
void AVLTree<K, V>::rotacioDre(BinaryTreeNode<K, V> *node){
    if(node->getLeft()->getRight() != nullptr){
        node->setLeft(node->getLeft()->getRight());
        node->getLeft()->getParent()->setRight(node);
    }
    else node->getLeft()->setRight(node);
    
    if(node->getParent() != nullptr) {
        if(node->getKey() < node->getParent()->getKey()){
            node->getParent()->setLeft(node->getLeft()->getParent());
            node->getLeft()->getParent()->setParent(node->getParent());
            node->setParent(node->getLeft()->getParent());
            node->getLeft()->setParent(node);
        }
        else{
            node->getParent()->setRight(node->getLeft()->getParent());
            node->getLeft()->getParent()->setParent(node->getParent());
            node->setParent(node->getLeft()->getParent());
            node->getLeft()->setParent(node);
        }
    }
    else{
        node->getLeft()->getParent()->setParent(nullptr);
        node->getLeft()->getParent()->setRight(node);
        node->setParent(node->getLeft()->getParent());
        node->getLeft()->setParent(node);
    }
}


template <class K, class V>
BinaryTreeNode <K, V>* AVLTree<K, V>::recalcularBF(BinaryTreeNode<K, V> *node){
    int bf = 0, max = 0;
    
    while(node != nullptr && abs(bf) < 2){
        if(node->getParent() != nullptr){
            int esquerra = 0, dreta = 0;
            if(node->getKey() > node->getParent()->getKey()){
                if(node->getParent()->getLeft() != nullptr) esquerra = node->getParent()->getLeft()->getHeight();
                node->getParent()->setBF(node->getHeight() - esquerra);
            }
            else{
                if(node->getParent()->getRight() != nullptr) dreta = node->getParent()->getRight()->getHeight();
                node->getParent()->setBF(dreta - node->getHeight());
            }
            
            bf = node->getParent()->getBF();
        }
        node = node->getParent();
    }
    return node;
}


template <class K, class V>
AVLTree<K, V>::~AVLTree() {
}



#endif /* AVLTREE_H */