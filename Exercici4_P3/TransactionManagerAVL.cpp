/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManagerAVL.cpp
 * Author: oscar
 * 
 * Created on 16 / de maig / 2021, 13:40
 */

#include "TransactionManagerAVL.h"
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include "BinarySearchTree.h"
#include "Transaction.h"
#include <cmath>
#include <sstream>

using namespace std;

TransactionManagerAVL::TransactionManagerAVL(float buyingFee, float sellingFee): AVLTree(){
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
}

TransactionManagerAVL::TransactionManagerAVL(string file_path, float buyingFee, float sellingFee): AVLTree(){
    loadFromFile(file_path);
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
}

TransactionManagerAVL::TransactionManagerAVL(const TransactionManagerAVL& orig): BinarySearchTree((BinarySearchTree<string,Transaction>) orig){
    this->buyingFee = orig.buyingFee;
    this->sellingFee = orig.sellingFee;
}

void TransactionManagerAVL::loadFromFile(string file_path){
    ifstream fin(file_path);
    string data;
    float quant;
    int id;
    vector<string> dades;
    getline(fin, data);
    while(!fin.eof()){
        getline(fin, data);
        dades = separador(data, ',');
        id = stoi(dades[1]);
        quant = stof(dades[2]);
        Transaction trans = Transaction(dades[0], id, quant);
        add(dades[0], trans);
    }
    fin.close();
}

vector<string> TransactionManagerAVL::separador(string input, char delimiter) {
    vector<string> dades;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        dades.push_back(temp);
    }

    return dades;
}

bool TransactionManagerAVL::hasData(string data) const{
    if(has(data) == true) return true;
    else return false;
}

void TransactionManagerAVL::showAll() const{
    int num, suma = 0, comp, compaux = 0;
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit\n");
    }
    do{
        cout << "Escriu el numero de dates que vols imprimir més petit o igual al nombre de dates disponibles\n";
        cin >> num;
    }while(num > size());
    suma = num;
    string data = "";
    BinaryTreeNode<string,Transaction> * node = p_root;
    do{
        int comp = 0;
        data = showAllAux(node, comp, num, data);
        do{
            cout << "Escriu (numero negatiu per sortir) quantes dates més vols imprimir de les que resten, l'acumulat no pot superar el total, " << num << "\n";
            cin >> num;
        } while(suma + num > size());
    } while(num  >= 1 );
    
    
}

string TransactionManagerAVL::showAllAux(BinaryTreeNode<string,Transaction>* node, int &comp, const int num, string data) const{
    if(node == nullptr) return data;
    string data2;
    if(node->getKey() > data || data == ""){
        data2 = showAllAux(node->getLeft(), comp, num, data);
        if(comp >= num) return data2;
        cout << node->getKey() << " : ";
        vector<Transaction> valors = node->getValues();
        for(int i = 0; i < valors.size(); i++){
            valors[i].print();
            if(i<valors.size()-1) cout << ", ";
        }
        cout << "\n";
        comp ++;
        if(comp >= num) return node->getKey();
    }
    data2 = showAllAux(node->getRight(), comp, num, data);
    if(comp >= num) return data2;
    else return data;
}

void TransactionManagerAVL::showAllReverse() const{
    int num, suma = 0;
    if(isEmpty()){
        throw invalid_argument("L'arbre està buit\n");
    }
    do{
        cout << "Escriu el numero de dates que vols imprimir més petit o igual al nombre de dates disponibles\n";
        cin >> num;
    }while(num > size());
    suma = num;
    
    do{
        int comp = 0;
        showAllReverseAux(this->p_root, comp, num);
        do{
            cout << "Escriu cuantes dates més vols imprimir de les que resten, no es pot superar el total\n";
            cin >> num;
        } while(suma + num > size());
    } while(num  >= 1);
    
}

void TransactionManagerAVL::showAllReverseAux(const BinaryTreeNode<string,Transaction>* node, int &comp, const int num) const{
    if(node == nullptr) return;
    else if(comp < num){
        showAllReverseAux(node->getRight(), comp, num);
        cout << node->getKey() << " : ";
        vector<Transaction> valors = node->getValues();
        for(int i = 0; i < valors.size(); i++){
            valors[i].print();
            if(i<valors.size()-1) cout << ", ";
        }
        cout << "\n";
        comp ++;
        showAllReverseAux(node->getLeft(), comp, num);
    }
}


void TransactionManagerAVL::showOldest() const{
    BinaryTreeNode<string, Transaction> *node = p_root;
    while(node->getRight() != nullptr)
        node = node->getRight();
    
    cout << node->getKey() << ": ";
    vector<Transaction> valors = node->getValues();
    for(int i = 0; i < valors.size(); i++){
        valors[i].print();
        if(i<valors.size()-1) cout << ", ";
    }
    cout << "\n";
}

void TransactionManagerAVL::showNewest() const{
    BinaryTreeNode<string, Transaction> *node = p_root;
    while(node->getLeft() != nullptr)
        node = node->getLeft();
    
    cout << node->getKey() << ": ";
    vector<Transaction> valors = node->getValues();
    for(int i = 0; i < valors.size(); i++){
        valors[i].print();
        if(i<valors.size()-1) cout << ", ";
    }
    cout << "\n";
}

float TransactionManagerAVL::feesInTotal() const{
    float total = 0;
    if(isEmpty()){
        return 0;
    }
    return feesInTotalInt(p_root);
}

float TransactionManagerAVL::feesInTotalInt(const BinaryTreeNode<string,Transaction>* node) const{
    float esquerra = 0;
    float dreta = 0;
    
    if(node->getLeft() != nullptr){
        esquerra = feesInTotalInt(node->getLeft());
    }
    if(node->getRight() != nullptr){
        dreta = feesInTotalInt(node->getRight());
    }
    
    return calculateFeesInNode(node) + esquerra + dreta;
}

/*En els mètodes següents, ho calcularem de manera una mica diferent però és correcte igual
En el mètode de sobre hem evitat anar a un node nul i hem retornat 0 i algun fill era nul i 
en els de sota entrem a qualsevol node i en cas de que sigui nul, retornem 0*/

float TransactionManagerAVL::feesSinceTime(string date) const{
    if(isEmpty()){
        throw invalid_argument("This tree is empty.\n");
    }
    else{
        return this->feesSinceTimeAux(date, this->p_root);
    }
}

float TransactionManagerAVL::feesSinceTimeAux(string date, const BinaryTreeNode<string,Transaction>* node) const{
    if(node == nullptr) return 0;
    else{
        if(node->getKey() < date) return feesSinceTimeAux(date, node->getRight());
        else return feesSinceTimeAux(date, node->getLeft()) + feesSinceTimeAux(date, node->getRight()) + calculateFeesInNode(node);;
        
    }
}

float TransactionManagerAVL::feesInTimeInterval(pair<string,string> interval) const{
    if(isEmpty()){
        throw invalid_argument("This tree is empty.\n");
    }
    else{
        return this->feesInTimeIntervalAux(interval, this->p_root);
    }
}

float TransactionManagerAVL::feesInTimeIntervalAux(pair<string,string> interval, const BinaryTreeNode<string,Transaction>* node) const{
    if(node == nullptr) return 0;
    else{
        if(node->getKey() < interval.first) return feesInTimeIntervalAux(interval, node->getRight());
        else if(node->getKey() > interval.second) return feesInTimeIntervalAux(interval, node->getLeft());
        else return feesInTimeIntervalAux(interval, node->getLeft()) + feesInTimeIntervalAux(interval, node->getRight()) + calculateFeesInNode(node);
        
    }
}

float TransactionManagerAVL::calculateFeesInNode(const BinaryTreeNode<string, Transaction>* node) const {
    float fees;
    
    //vector<Transaction> trans = node->getValues();
    for(int i = 0; i < node->getValues().size(); i++){
        if(node->getValues()[i].getQuantitat() > 0)
            fees += abs(node->getValues()[i].getQuantitat()) * this->sellingFee;
        
        else  fees += abs(node->getValues()[i].getQuantitat()) * this->buyingFee;
        
            
    }
    
    return fees;
}

BinaryTreeNode<string, Transaction>* TransactionManagerAVL::findDate(const string& data) const{
    return find(data);
    
}

TransactionManagerAVL::~TransactionManagerAVL() {
}

