//
// Created by Nik on 8/10/2022.
//

#include "Withdraw.h"

//Constructor
Withdraw::Withdraw(int id, int money, int fundID, bool isSuccessful)
{
    //set IDs, references numbers, and the amount
    this->accID = id;
    this->amount = money;
    this->fundReference = fundID;
    this->success = isSuccessful;
}

//Destructor
Withdraw::~Withdraw()
{
    //empty destructor
}

//Helper method for operator<< and to override Transaction's displayTransaction function
ostream &Withdraw::displayTransaction(ostream &os) const
{
    os << "W " << accID << fundReference << " "<< amount; //good withdraw
    if(!(success))
        os << " (failed)" << endl; //failed withdraw

    return os;
}
