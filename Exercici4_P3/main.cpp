/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: oscar
 *
 * Created on 16 / de maig / 2021, 13:35
 */

#include <cstdlib>
#include <fstream>
#include "Transaction.h"
#include "TransactionManager.h"
#include "BinarySearchTree.h"
#include "BinaryTreeNode.h"
#include <utility>
#include <chrono>
#include <iostream>

using namespace std;

/*
 * 
 */

//Aquest exercici no compila ja que el exercici 3 no l'he pogut acabar de solucionar del tot.



// *** No se si és problema de que tinc mac però no he aconseguit fer que funciones la manera de calcular
// el temps d'execució que ens vau proporcionar. Tot i així, he comprovat que tots els fitxers 
// funcionen (en el primer exerci) treient la ultima linia buida d'aquests.

int main(int argc, char** argv) {
    int opcio;
    float balanc = 0;
    string data1, data2;
    pair<string, string> interval;
    
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
    
    TransactionManagerAVL manager = TransactionManagerAVL();
    
    do{
        
        do{
           cout << "Selecciona una opció:\n";
           cin >> opcio;
        } while (opcio < 1 || opcio > 10);
    

        string ruta;
        switch(opcio){
            case 1: 
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
                //chrono::time_point<chrono::system_clock> instantInicial, instantFinal;
                //instantInicial= chrono::system_clock::now();
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
                //instantFinal  = chrono::system_clock::now();
                //chrono::duration<double> temps = instantFinal-instantInicial;
                //cout << "Temps transcorregut: " << temps << " s." << endl;
                break;
        }
    }while(opcio != 10);
    
    
    
    
    
    return 0;
}
