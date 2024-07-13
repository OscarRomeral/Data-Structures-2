/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManagerAVL.h
 * Author: oscar
 *
 * Created on 16 / de maig / 2021, 13:40
 */

#ifndef TRANSACTIONMANAGERAVL_H
#define TRANSACTIONMANAGERAVL_H
#include <string>
#include "AVLTree.h"
#include "BinaryTreeNode.h"
#include "Transaction.h"

class TransactionManagerAVL : protected AVLTree<string, Transaction>{
public:
    TransactionManagerAVL(float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManagerAVL(string file_path, float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManagerAVL(const TransactionManagerAVL& orig);
    virtual ~TransactionManagerAVL();

    void loadFromFile(string file_path);
    void showAll() const;
    void showAllReverse() const;
    void showOldest() const;
    void showNewest() const;

    float feesInTotal() const;
    float feesSinceTime(string date) const;
    float feesInTimeInterval(pair<string,string> interval) const;
    float calculateFeesInNode(const BinaryTreeNode<string, Transaction>* node) const;
    
    bool hasData(string data) const;
    BinaryTreeNode<string,Transaction>* findDate(const string& data) const;

 private:
    float sellingFee;
    float buyingFee; 
    string showAllAux(BinaryTreeNode<string,Transaction>* node, int &comp, const int num, string data) const;
    void showAllReverseAux(const BinaryTreeNode<string,Transaction>* node, int &comp, const int num) const;
    float feesInTotalInt(const BinaryTreeNode<string,Transaction>* node) const;
    float feesSinceTimeAux(string date, const BinaryTreeNode<string,Transaction>* node) const;
    float feesInTimeIntervalAux(pair<string,string> interval, const BinaryTreeNode<string,Transaction>* node) const;
    vector<string> separador(string input, char delimiter);
};

#endif /* TRANSACTIONMANAGER_H */

