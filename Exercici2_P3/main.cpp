/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: oscar
 *
 * Created on 10 / de maig / 2021, 09:12
 */

#include <cstdlib>
#include <fstream>
#include "Transaction.h"
#include "TransactionManager.h"
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"
#include <utility>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <iostream>

using namespace std;

/*
 * 
 */



int main(int argc, char** argv) {
    int opcio;
    float balanc = 0;
    string data1, data2;
    pair<string, string> interval;
    unsigned t0, t1;
    double time;
    
    cout << "Menú\n";
    cout << "1. Especificar ruta fitxer.\n";
    cout << "2. Mostrar totes les transaccions ordenades temporalment.\n";
    cout << "3. Mostrar totes les transaccions en ordre temporal invers.\n";
    cout << "4. Mostrar les transaccions del primer instant de temps.\n";
    cout << "5. Mostrar les transaccions del darrer instant de temps.\n";
    cout << "6. Mostrar la comissió recaptada per totes les transaccions.\n";
    cout << "7. Mostrar la comissió recaptada a partir d'una data específica.\n";
    cout << "8. Mostrar comissió recaptada entre 2 dates.\n";
    cout << "9. Mostrar el balanç de les transaccions efectuades en les dates del fitxer queries.txt.\n";
    cout << "10. Sortir.\n\n";
    
    TransactionManager manager = TransactionManager();
    
    do{
        
        do{
           cout << "Selecciona una opció:\n";
           cin >> opcio;
        } while (opcio < 1 || opcio > 10);
    

        string ruta;
        switch(opcio){
            case 1: 
                
                // **** Cal treure la ultima linia (buida) dels fitxers per evitar segmentation fault ****
                
                cout << "Escriu la ruta del fitxer que vols carregar:\n";
                cin >> ruta;
                manager.loadFromFile(ruta);
                break;
            case 2:
                manager.showAll();
                break;
            case 3:
                manager.showAllReverse();
                break;
            case 4:
                manager.showOldest();
               break;
            case 5:
                manager.showNewest();
                break;
            case 6:
                cout << manager.feesInTotal() << "\n";
                break;
            case 7:
                getline(cin, data1);
                cout << "Indica la data des de la que vols saber les comissions:\n";
                getline(cin, data1);
                cout << manager.feesSinceTime(data1) << "\n";
                break;
            case 8:
                getline(cin, interval.first);
                cout << "Indica la data des de la que vols saber les comissions:\n";
                getline(cin, interval.first);
                cout << "Indica la data fins la que vols saber les comissions:\n";
                getline(cin, interval.second);
                cout << manager.feesInTimeInterval(interval) << "\n";
                break;
            case 9:
                ifstream fin("queries.txt");
                string data;
                while(!fin.eof()){
                    getline(fin, data);
                    if(manager.findDate(data) != nullptr){
                        BinaryTreeNode<string, Transaction>* node = manager.findDate(data);
                        balanc += manager.calculateFeesInNode(node);
                    }
                }
                cout << "El valor de l'acomulat és: " << balanc << "\n";
               
                break;
        }
    }while(opcio != 10);
    
    
    
    
    
    return 0;
}


