/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transaction.cpp
 * Author: oscar
 * 
 * Created on 10 / de maig / 2021, 09:15
 */

#include "Transaction.h"
#include <iostream>

using namespace std;

Transaction::Transaction(const string data, const int id, const float quantitat) {
    this->dataTransaction = data;
    this->id = id;
    this->quantitat = quantitat;
}

Transaction::Transaction(const Transaction& orig) {
    this->dataTransaction = orig.getData();
    this->id = orig.getId();
    this->quantitat = orig.getQuantitat();
}

string Transaction::getData() const{
    return this->dataTransaction;
}

int Transaction::getId() const{
    return this->id;
}

float Transaction::getQuantitat() const{
    return this->quantitat;
}
    
void Transaction::setData(const string data){
    this->dataTransaction = data;
}

void Transaction::setId(const int id){
    this->id = id;
}

void Transaction::setQuantitat(const float quantitat){
    this->quantitat = quantitat;
}

void Transaction::print(){
    cout << "(" << getId() << ", " << getQuantitat() << ")";
}

Transaction::~Transaction() {
}

