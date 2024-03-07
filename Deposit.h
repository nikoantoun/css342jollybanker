//
// Created by Niko on 8/10/2022.
//

#ifndef PROGRAM_5_CODE_DEPOSIT_H
#define PROGRAM_5_CODE_DEPOSIT_H
#include "Transaction.h"

using namespace std;

class Deposit : public Transaction
{
    //Overload operator for Deposit
    friend ostream& operator<<(ostream& os, const Deposit& d)
    {
        return d.displayTransaction(os); //invokes display: implemented in cpp file to override in subclasses
    }

public:
    //Constructor
    Deposit(int accID, int money, int fundID, bool successful);

    //Destructor
    ~Deposit();

    //Helper method for operator<< and to override Transaction's displayTransaction function
    ostream& displayTransaction(ostream& out) const override;


private:
    int amount;
    int fundReference;
};


#endif //PROGRAM_5_CODE_DEPOSIT_H
