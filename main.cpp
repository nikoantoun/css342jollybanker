#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

int main()
{
    //Main test
    Bank BankOf342;
    BankOf342.readTransactionFile("BankTransIn.txt");
    cout << BankOf342 << endl;

    //Other tests
    /*
    Bank Wells342;
    cout << "Wells342 Bank" << endl;
    Wells342.readTransactionFile("BankTrans.txt");
    cout << endl;

    Bank CSS342Federal;
    cout << "CSS342Federal" << endl;
    CSS342Federal.readTransactionFile("BankTrans1.txt");
    cout << endl;


    Bank Students342CreditUnion;
    cout << "Students342CreditUnion" << endl;
    Students342CreditUnion.readTransactionFile("BankTrans2.txt");
    cout << endl;


    Bank CSS342CommunityBank;
    cout << "CSS342CommunityBank" << endl;
    CSS342CommunityBank.readTransactionFile("BankTrans3.txt");
    cout << endl;
     */

    return 0;
}
