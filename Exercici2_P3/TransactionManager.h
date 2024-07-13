/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransactionManager.h
 * Author: oscar
 *
 * Created on 10 / de maig / 2021, 10:21
 */

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <string>
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"
#include "Transaction.h"

class TransactionManager : protected BinarySearchTree<string, Transaction> {
 public:
    TransactionManager(float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManager(string file_path, float buyingFee = 0.02, float sellingFee = 0.03);
    TransactionManager(const TransactionManager& orig);
    virtual ~TransactionManager();

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

