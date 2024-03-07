//
// Created by Niko on 8/10/2022.
//

#include "Bank.h"
#include "Transaction.h"
#include "Deposit.h"
#include "Withdraw.h"
#include "Transfer.h"

using namespace std;

//Constructors
Bank::Bank()
{
    //Empty constructor
}

//Destructor
Bank::~Bank()
{
    //Empty destructor
}

//Member functions
bool Bank::readTransactionFile(const string& fileName) //reads file
{
    //Read file and push into queue
    ifstream inFile;
    inFile.open(fileName);
    if(!inFile)
    {
        cout << "Error: Cannot open file" << endl;
        return false;
    }
    //cout << "File opened successfully" << endl;
    string next;
    while(getline(inFile, next))
        transactions.push(next);

    //Process transactions into appropriate place
    queue<string> trCopy = copyTransactions(transactions);
    while(!trCopy.empty())
    {
        //cout << "INVOKED" << endl;
        stringstream inString; //processes the strings
        string processType;
        inString << trCopy.front();
        inString >> processType;

        if(processType == "O") //Open
        {
            string first, last;
            int accID;
            inString >> first >> last >> accID;
            Client openAcc(last, first, accID); //uses the Client class for account information
            toOpen = new Account(openAcc); //creates new Account using data from Client
            accountTree.Insert(toOpen); //adds new account to tree
        }
        else if(processType == "D") //Deposit
        {
             Account* depositAcc;
             int count, accID, fundID, amount;
             bool isSuccessful;

             inString >> count >> amount; //reads the amount

             accID = count / 10; //gets the account number from file
             fundID = count % 10; //number for the fund type

             if(accountTree.Retrieve(accID, depositAcc))
             {
                 //make new deposit and add to history
                 isSuccessful = depositAcc->depositFundAmount(fundID, amount);
                 depositAcc->addTransaction(fundID, new Deposit(accID, amount, fundID, isSuccessful));
             }
             else
                 cout << "Unable to deposit funds: Account ID not found";
        }
        else if(processType == "W") //Withdraw
        { //similar to deposit, but creates new Withdraw and avoids duplicates when involved with other funds
            Account* withdrawAcc;
            int count, accID, fundID, amount;
            bool isSuccessful;

            inString >> count >> amount;

            fundID = count % 10; //gets the account number from file
            accID = count / 10; //number for the fund type

            if(accountTree.Retrieve(accID, withdrawAcc))
            {
                //make new withdraw and add to history
                isSuccessful = withdrawAcc->withdrawFundAmount(fundID, amount);
                if(!withdrawAcc->getWithdrawCheck()) //to avoid duplicate Withdraws when a different fund covers an outstanding balance
                    withdrawAcc->addTransaction(fundID, new Withdraw(accID, amount, fundID, isSuccessful));
            }
            else
                cout << "Unable to withdraw funds: Account ID invalid" << endl;
        }
        else if(processType == "T") //Transfer
        {
            Account *fromAcc, *toAcc;
            int countFrom, countTo, fromAccID, toAccID, fromFundID, toFundID, money;
            bool isSuccessful;

            inString >> countFrom >> money >> countTo;

            fromAccID = countFrom / 10; //gets the account number from file
            fromFundID = countFrom % 10; //number for the fund type
            toAccID = countTo / 10; //gets the account number from file
            toFundID = countTo % 10; //number for the fund type

            //make new transfer and add to history
            if(accountTree.Retrieve(fromAccID, fromAcc) && accountTree.Retrieve(toAccID, toAcc))
            { //successful case
                isSuccessful = fromAcc->transferFundAmount(toAcc, fromFundID, toFundID, money);
                fromAcc->addTransaction(fromFundID, new Transfer(fromAccID, toAccID, fromFundID, toFundID, money, isSuccessful));
                toAcc->addTransaction(toFundID, new Transfer(fromAccID, toAccID, fromFundID, toFundID, money, isSuccessful));
            } //below: error cases
            else if(!(accountTree.Retrieve(fromAccID, fromAcc)) && !(accountTree.Retrieve(toAccID, toAcc)))
                cout << "Unable to transfer funds: Both account ID's are invalid" << endl;
            else if(!(accountTree.Retrieve(fromAccID, fromAcc)))
                cout << "Unable to transfer funds: #" << fromAccID << " ID is invalid" << endl;
            else if(!(accountTree.Retrieve(toAccID, toAcc)))
                cout << "Unable to transfer funds: #" << toAccID << " ID is invalid" << endl;
            else
                cout << "Unable to transfer funds: Please try again" << endl;
        }
        else if(processType == "H") //History
        {
            Account* history;
            int count, accID, fundID;
            inString >> count;
            if(count >= 10000)
            {
                accID = count / 10; //gets the account number from file
                fundID = count % 10; //number for the fund type

                if(accountTree.Retrieve(accID, history))
                { //print history
                    cout << "Transaction History for " << history->getClient().getForename();
                    cout << " " << history->getClient().getSurname() << " by fund." << endl;
                    history->getFundHistory(fundID);
                    cout << endl;
                }
                else
                    cout << "Unable to find account history: Account ID invalid" << endl;
            }
            else
            {
                accID = count;
                if(accountTree.Retrieve(accID, history))
                { //print history
                    cout << "Transaction History for " << history->getClient().getForename();
                    cout << " " << history->getClient().getSurname() << " by fund." << endl;
                    history->getAccHistory();
                    cout << endl;
                }
                else
                    cout << "Unable to find account history: Account ID invalid" << endl;
            }
        }
        else
            cout << "Invalid input: " << processType << endl;

        //cout << "INVOKED" << endl;
        trCopy.pop();
    }
    return true; //read file was successful
}

queue<string> Bank::copyTransactions(const queue<string> &toCopy)
{ //avoids any data from being lost when processing transactions
    queue<string> copy = toCopy;
    return copy;
}

void Bank::displayBalances() const //display all account balances
{
    accountTree.Display(); //invokes display in BSTree
}
