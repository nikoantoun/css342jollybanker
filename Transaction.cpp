//
// Created by Nik on 8/10/2022.
//

#include "Transaction.h"

Transaction::Transaction() //default constructor
{
    this->accID = -1;
    this->success = false;
}

Transaction::Transaction(int id, bool isSuccessful) //2-arg constructor
{
    this->accID = id;
    this->success = isSuccessful;
}

//Destructor
Transaction::~Transaction()
{
    //empty destructor
}

//Getters
int Transaction::getID() const
{
    return this->accID;
}

bool Transaction::getTransactionStatus() const
{
    return this->success;
}

ostream& Transaction::displayTransaction(ostream& os) const
{ //to override in subclasses: Deposit, Withdraw, and Transfer
    os << "Transaction " << accID; //good transaction
    if(!(success))
        os << " (failed)" << endl; //failed transaction
    return os;
}
