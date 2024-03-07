//
// Created by Niko on 8/10/2022.
//

#include "Account.h"
#include "Withdraw.h"

//Constructors
Account::Account() //Default constructor
{
    Client c;
    setWithdrawCheck(false); //default: only set to true if an Index fund's withdraw is covered by the other
}

//Copy constructor (mainly used)
Account::Account(const Client& copy) : customer{copy}, withdrawCheck{false} {}


//Destructor
Account::~Account()
{
    //Empty destructor
}

//Member Functions
bool Account::depositFundAmount(int fundID, int amount)
{
    if(amount < 0) //negative amount inputted
        return false;

    if(isValidFund(fundID)) //checks requested Fund's ID validity
    {
        fundTypes[fundID].fundBalance += amount; //adds balance
        return true;
    }
    else //not valid
        return false;
}

bool Account::withdrawFundAmount(int fundID, int amount)
{
    if(!isValidFund(fundID))
        return false;

    if(fundTypes[fundID].fundBalance - amount >= 0) //balance - amount >= 0
    {
        fundTypes[fundID].fundBalance -= amount;
        return true;
    }

    //Cases where other funds has an available balance but original does not
    if(fundID == 0 || fundID == 1) //if the fund is a money market
    {
        int amountRemaining = amount - fundTypes[fundID].fundBalance;
        for(int i = 0; i < fundTypes.size(); i++)
        {
            if(fundTypes[i].fundBalance - amountRemaining >= 0)
            {
                fundTypes[fundID].fundBalance = 0; //sets total balance to 0
                fundTypes[i].fundBalance -= amountRemaining; //withdraws from other money market
                return true;
            }
        }
        return false;
    }
    else if(fundID == 2 || fundID == 3) //if the fund is a bond
    {
        int amountRemaining = amount - fundTypes[fundID].fundBalance;
        for(int i = 2; i < fundTypes.size(); i++)
        {
            if(fundTypes[i].fundBalance - amountRemaining >= 0)
            {
                if(fundID == 2) //long-term bond
                {
                    this->addTransaction(fundID, new Withdraw(this->getClient().getID(), fundTypes[fundID].fundBalance, fundID, true));

                    fundTypes[fundID].fundBalance = 0; //sets total balance to 0
                    fundTypes[i+1].fundBalance -= amountRemaining;

                    this->setWithdrawCheck(true); //to avoid adding an extra Withdraw to history

                    //add the additional transaction
                    this->addTransaction(i+1, new Withdraw(this->getClient().getID(), fundTypes[i+1].fundBalance, i+1, true));
                    return true;
                }
                if(fundID == 3) //short-term bond
                {
                    //Add original transaction
                    this->addTransaction(fundID, new Withdraw(this->getClient().getID(), fundTypes[fundID].fundBalance, fundID, true));

                    fundTypes[fundID].fundBalance = 0; //sets total balance to 0
                    fundTypes[i-1].fundBalance -= amountRemaining;

                    this->setWithdrawCheck(true); //to avoid adding an extra Withdraw to history

                    //add the additional transaction
                    this->addTransaction(i-1, new Withdraw(this->getClient().getID(), fundTypes[i-1].fundBalance, i-1, true));

                    return true;
                }
            }
        }
        //cout << "Overdraft error." << endl;
        return false;
    }

    //No available funds to withdraw
    cout << "ERROR: Overdraft. Not enough funds to withdraw $" << amount << " from ";
    cout << this->getClient().getForename() << " " << this->getClient().getSurname() << " (Available funds from ";
    cout << fundTypes[fundID] << ")" << endl;
    return false;
}

bool Account::transferFundAmount(Account* toAccount, int aFundID, int bFundID, int amount)
{
    if(!isValidFund(aFundID) || !isValidFund(bFundID))
        return false;

    if(fundTypes[aFundID].fundBalance - amount >= 0) //if the balance is sufficient
    {
        fundTypes[aFundID].fundBalance -= amount;
        toAccount->depositFundAmount(bFundID, amount); //deposits to account
        return true;
    }
    else
    {
        cout << "Transfer error: Invalid amount." << endl;
        return false;
    }
}

bool Account::addTransaction(int fundID, Transaction* t)
{
    if(isValidFund(fundID))
    {
        fundTypes[fundID].fundHistory.push_back(t); //adds the transaction to the fund's history
        return true;
    }
    else
        return false; //invalid
}

bool Account::isValidFund(int fundID)
{
    if(fundID < 0 || fundID > 9) //checks requested Fund's ID validity
    {
        //cout << "Invalid Fund ID." << endl; //prints error
        return false;
    }
    else //fund's ID is valid
        return true;
}

//Getters
void Account::getAccHistory() const
{
    for(int i = 0; i < fundTypes.size(); i++)
    {
        //if the fund has money or any transaction history, print
        if(fundTypes[i].fundBalance != 0 || fundTypes[i].fundHistory.size() != 0)
        {
            cout << fundTypes[i] << endl;
            for (int j = 0; j < fundTypes[i].fundHistory.size(); j++)
                cout << "  " << *(fundTypes[i].fundHistory[j]) << endl; //prints the transaction
        }
    }
    //cout << endl;
}

void Account::getFundHistory(const int fundID) const
{
    cout << fundTypes[fundID] << endl;
    for(int i = 0; i < fundTypes[fundID].fundHistory.size(); i++)
        cout << "  " << *(fundTypes[fundID].fundHistory[i]); //prints the fund
}

Client Account::getClient() const //getter for client
{
    return this->customer;
}

bool Account::getWithdrawCheck() const //getter to help withdraw
{
    return this->withdrawCheck;
}

void Account::setWithdrawCheck(bool didCover) //setter to help withdraw
{
    this->withdrawCheck = didCover;
}

