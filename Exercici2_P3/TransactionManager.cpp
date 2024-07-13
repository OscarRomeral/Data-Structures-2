/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManager.cpp
 * Author: oscar
 * 
 * Created on 10 / de maig / 2021, 10:21
 */

#include "TransactionManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include "BinarySearchTree.h"
#include "Transaction.h"
#include <cmath>
#include <sstream>

using namespace std;

TransactionManager::TransactionManager(float buyingFee, float sellingFee): BinarySearchTree(){
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
}

TransactionManager::TransactionManager(string file_path, float buyingFee, float sellingFee): BinarySearchTree(){
    loadFromFile(file_path);
    this->buyingFee = buyingFee;
    this->sellingFee = sellingFee;
}

TransactionManager::TransactionManager(const TransactionManager& orig): BinarySearchTree((BinarySearchTree<string,Transaction>) orig){
    this->buyingFee = orig.buyingFee;
    this->sellingFee = orig.sellingFee;
}

void TransactionManager::loadFromFile(string file_path){
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
    //Llegim del fitxer i separem el string per les comes, després convertim al tipus desitjat
}

vector<string> TransactionManager::separador(string input, char delimiter) {
    vector<string> dades;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        dades.push_back(temp);
    }

    return dades;
}

bool TransactionManager::hasData(string data) const{
    if(has(data) == true) return true;
    else return false;
}

void TransactionManager::showAll() const{
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
    
    //Demanem valors veridics per a la nostre llista i cridem al mètode recursiu
    
    
}

string TransactionManager::showAllAux(BinaryTreeNode<string,Transaction>* node, int &comp, const int num, string data) const{
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
    //Aquest mètode va ensenyant les dates fins que arriba a la quantitat que ens demanen
    //Després retorna la data a la qual ens hem quedat per així puguer reprendre al seguent cop
    //Passem per referència el comptador per tal de que es vagi modificant durant les crides recursives
}

void TransactionManager::showAllReverse() const{
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
    //Operació inversa que ShowAll
    
}

void TransactionManager::showAllReverseAux(const BinaryTreeNode<string,Transaction>* node, int &comp, const int num) const{
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


void TransactionManager::showOldest() const{
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
    //Busca el node que està a la esquerra del tot i l'ensenya per pantalla
}

void TransactionManager::showNewest() const{
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
    //Busca el node que està a la dreta del tot i l'ensenya per pantalla
}

float TransactionManager::feesInTotal() const{
    float total = 0;
    if(isEmpty()){
        return 0;
    }
    return feesInTotalInt(p_root);
}

float TransactionManager::feesInTotalInt(const BinaryTreeNode<string,Transaction>* node) const{
    float esquerra = 0;
    float dreta = 0;
    
    if(node->getLeft() != nullptr){
        esquerra = feesInTotalInt(node->getLeft());
    }
    if(node->getRight() != nullptr){
        dreta = feesInTotalInt(node->getRight());
    }
    
    return calculateFeesInNode(node) + esquerra + dreta;
    //crida el mètode recursiu en cas que tingui fills
}

/*En els mètodes següents, ho calcularem de manera una mica diferent però és correcte igual
En el mètode de sobre hem evitat anar a un node nul i hem retornat 0 i algun fill era nul i 
en els de sota entrem a qualsevol node i en cas de que sigui nul, retornem 0*/

float TransactionManager::feesSinceTime(string date) const{
    if(isEmpty()){
        throw invalid_argument("This tree is empty.\n");
    }
    else{
        return this->feesSinceTimeAux(date, this->p_root);
    }
}

float TransactionManager::feesSinceTimeAux(string date, const BinaryTreeNode<string,Transaction>* node) const{
    if(node == nullptr) return 0;
    else{
        if(node->getKey() < date) return feesSinceTimeAux(date, node->getRight());
        else return feesSinceTimeAux(date, node->getLeft()) + feesSinceTimeAux(date, node->getRight()) + calculateFeesInNode(node);;
        //Tenim en compte les dates que són més grans que la donada, ho fem recursivament
    }
}

float TransactionManager::feesInTimeInterval(pair<string,string> interval) const{
    if(isEmpty()){
        throw invalid_argument("This tree is empty.\n");
    }
    else{
        return this->feesInTimeIntervalAux(interval, this->p_root);
    }
}

float TransactionManager::feesInTimeIntervalAux(pair<string,string> interval, const BinaryTreeNode<string,Transaction>* node) const{
    if(node == nullptr) return 0;
    else{
        if(node->getKey() < interval.first) return feesInTimeIntervalAux(interval, node->getRight());
        else if(node->getKey() > interval.second) return feesInTimeIntervalAux(interval, node->getLeft());
        else return feesInTimeIntervalAux(interval, node->getLeft()) + feesInTimeIntervalAux(interval, node->getRight()) + calculateFeesInNode(node);
        //Garanteix que els valors que tenim en compte es mantinguin dins de l'interval donat
    }
}

float TransactionManager::calculateFeesInNode(const BinaryTreeNode<string, Transaction>* node) const {
    float fees;
    
    //vector<Transaction> trans = node->getValues();
    for(int i = 0; i < node->getValues().size(); i++){
        if(node->getValues()[i].getQuantitat() > 0)
            fees += abs(node->getValues()[i].getQuantitat()) * this->sellingFee;
        
        else  fees += abs(node->getValues()[i].getQuantitat()) * this->buyingFee;
        
            
    }
    
    return fees;
}

BinaryTreeNode<string, Transaction>* TransactionManager::findDate(const string& data) const{
    return find(data);
    
}

TransactionManager::~TransactionManager() {
}

