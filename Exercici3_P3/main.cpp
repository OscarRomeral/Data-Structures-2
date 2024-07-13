/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: oscar
 *
 * Created on 13 / de maig / 2021, 19:33
 */

#include <cstdlib>

#include "BinarySearchTree.h"
#include "AVLTree.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    AVLTree<int, int> * tree1 = new AVLTree<int,int>;

    int testKeys[] = {2,0,8,45,76,5,3, 40};
    int testValues [] = {5, 5, 1, 88, 99, 12, 9, 11};
        
    int comp = 0;
    for (int i: testKeys){
        tree1->afegirBalancejar(i, testValues[comp]);
        comp++;
    }
        
    cout << "Preorder = { " ;   
    tree1->showKeysPreorder();
    cout <<" }\n";
    cout << "Inorder = { " ;
    tree1->showKeysInorder();
    cout <<" }\n";
    cout << "Postorder = { " ;
    tree1->showKeysPostorder();
    cout <<" }\n\n";
        
    AVLTree <int, int> *tree2 = new AVLTree<int,int>(*tree1);
    
    if(tree1->equals(*tree2) == true){
        cout << "Cert\n";
    }    
    else cout << "Fals\n";
    tree1->afegirBalancejar(1, 10);
    if(tree1->equals(*tree2) == true){
        cout << "Cert\n";
    }    
    else cout << "Fals\n";

    return 0;
}

