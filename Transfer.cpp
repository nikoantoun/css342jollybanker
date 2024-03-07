//
// Created by Nik on 8/10/2022.
//

#include "Transfer.h"

//Constructor
Transfer::Transfer(int fromAccID, int toAccID, int aFundID, int bFundID, int money, bool isSuccessful) //6-arg constructor
{
    //set IDs, references numbers, and the amount
    this->accID = fromAccID;
    this->transferToID = toAccID;
    this->fundReferenceA = aFundID;
    this->fundReferenceB = bFundID;
    this->amount = money;
    this->success = isSuccessful;
}

//Destructor
Transfer::~Transfer()
{
    //empty destructor
}

//Helper method for operator<< and to override Transaction's displayTransaction function
ostream &Transfer::displayTransaction(ostream &os) const
{
    os << "T " << accID << fundReferenceA << " " << amount << " " << transferToID << fundReferenceB; //good transfer
    if(!(success)) //failed transfer
        os << " (failed)" << endl;
    return os;
}
