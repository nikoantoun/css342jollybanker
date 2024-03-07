//
// Created by Nik on 8/10/2022.
//

#include "Deposit.h"

//Constructor
Deposit::Deposit(int id, int money, int fundID, bool isSuccessful) //4-arg constructor
{
    //set IDs, references numbers, and the amount
    this->accID = id;
    this->amount = money;
    this->fundReference = fundID;
    this->success = isSuccessful;
}

//Destructor
Deposit::~Deposit()
{
    //empty destructor
}

ostream &Deposit::displayTransaction(ostream &os) const
{
    os << "D " << accID << fundReference << " "<< amount; //good deposit
    if(!(success))
        os << " (failed)" << endl; //failed deposit

    return os;
}