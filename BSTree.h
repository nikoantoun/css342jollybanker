//
// Created by Niko on 8/10/2022.
//

#ifndef PROGRAM_5_CODE_BSTREE_H
#define PROGRAM_5_CODE_BSTREE_H
#include <iostream>
#include <string>
#include "Account.h"
#include "Transaction.h"
#include "Deposit.h"
#include "Withdraw.h"
#include "Transfer.h"

using namespace std;

class BSTree
{
    //Output overload for BSTree
    friend ostream& operator<<(ostream& os, const BSTree& retTree)
    {
        return retTree.displayHelper(retTree.head, os); //invokes recursive display helper
    }

public:

    //Constructors
    BSTree();
    ~BSTree();

    //Member functions
    bool Insert(Account *);

    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Retrieve(const int &, Account * &) const;

    // displays the contents of a tree to cout
    void Display() const;
    void Empty();
    bool isEmpty() const;


private:
    struct Node //provided
    {
        //explicit Node(Account* acc) : pAcct{acc}, left{nullptr}, right{nullptr} {};
        Node(Account *acc) //check
        {
            pAcct = acc;
            right = nullptr;
            left = nullptr;
        }
        Account *pAcct;
        Node *right;
        Node *left;
    };
    Node *head;

    //Recursive helper methods
    bool insertHelper(Account*, Node*);
    ostream& displayHelper(Node*, ostream&) const;
    void emptyHelper(Node*);
};


#endif //PROGRAM_5_CODE_BSTREE_H
