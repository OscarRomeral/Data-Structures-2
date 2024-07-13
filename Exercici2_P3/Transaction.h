/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Transaction.h
 * Author: oscar
 *
 * Created on 10 / de maig / 2021, 09:15
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

using namespace std;

class Transaction {
public:
    Transaction(const string data, const int id, const float quantitat);
    Transaction(const Transaction& orig);
    virtual ~Transaction();
    
    string getData() const;
    int getId() const;
    float getQuantitat() const;
    
    void setData(const string data);
    void setId(const int id);
    void setQuantitat(const float quantitat);
    
    void print();
    
private:
    string dataTransaction;
    int id;
    float quantitat;
    

};

#endif /* TRANSACTION_H */

