/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: oscar
 *
 * Created on 21 / d’abril / 2021, 14:22
 */

#include <cstdlib>

#include "BinarySearchTree.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    BinarySearchTree<int, int> tree1;

    int testKeys[] = {2,0,8,45,76,5,3,40};
    int testValues [] = {5, 5, 1, 88, 99, 12, 9, 11};
        
    int comp = 0;
    for (int i: testKeys){
            tree1.add(i, testValues[comp]);
            comp++;
    }
        
    cout << "Preorder = { " ;   
    tree1.showKeysPreorder();
    cout <<" }\n";
    cout << "Inorder = { " ;
    tree1.showKeysInorder();
    cout <<" }\n";
    cout << "Postorder = { " ;
    tree1.showKeysPostorder();
    cout <<" }\n\n";
        
    BinarySearchTree <int, int>tree2(tree1);
    
    if(tree1.equals(tree2) == true){
        cout << "Cert\n";
    }    
    else cout << "Fals\n";
    tree1.add(1, 10);
    if(tree1.equals(tree2) == true){
        cout << "Cert\n";
    }    
    else cout << "Fals\n";

    return 0;
}

