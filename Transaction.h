//
// Created by Niko on 8/10/2022.
//

#ifndef PROGRAM_5_CODE_TRANSACTION_H
#define PROGRAM_5_CODE_TRANSACTION_H
#include <iostream>
#include <string>

using namespace std;

class Transaction {
    //Output operator overload: Displays transactions
    friend ostream& operator<<(ostream& os, const Transaction& t)
    {
        return t.displayTransaction(os); //invokes display: implemented in cpp file to override in subclasses
    }

public:
    //Constructors
    Transaction();
    Transaction(int id, bool isSuccessful);

    //Destructor
    ~Transaction();

    //Member functions
    virtual ostream& displayTransaction(ostream& os) const; //made virtual to override in subclasses

    //Getters
    int getID() const;
    bool getTransactionStatus() const;

protected:
    int accID;
    bool success;
};


#endif //PROGRAM_5_CODE_TRANSACTION_H
