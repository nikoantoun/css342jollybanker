//
// Created by Niko on 8/10/2022.
//

#ifndef PROGRAM_5_CODE_BANK_H
#define PROGRAM_5_CODE_BANK_H
#include <iostream>
#include <ostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include "Account.h"
#include "BSTree.h"

using namespace std;

class Bank
{

    //Output operator overload: display transactions
    friend ostream& operator<<(ostream& os, const Bank& b)
    {
        //os << "Displaying Bank: " << endl;
        b.displayBalances(); //display balances: invoked from function, implemented in BSTree: Display()
        return os;
    }

public:
    //Constructors
    Bank();

    //Destructor
    ~Bank();

    //Member functions
    bool readTransactionFile(const string& fileName); //reads file
    void displayBalances() const; //display all account balances

private:
    Account* toOpen;
    BSTree accountTree; //tree to store accounts

    //transaction queue
    queue<string> transactions;

    //copy the accounts queue so no data is lost
    queue<string> copyTransactions(const queue<string> &toCopy);
};


#endif //PROGRAM_5_CODE_BANK_H
