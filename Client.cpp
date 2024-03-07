//
// Created by Nik on 8/16/2022.
//

#include "Client.h"

//Constructors
Client::Client() //Default constructor
{
    this->surname = "";
    this->forename = "";
    this->accID = -1;
}

Client::Client(string first, string last, int clientAccID) //3-arg Constructor
{
    this->forename = first;
    this->surname = last;
    this->accID = clientAccID;
}

//Destructor
Client::~Client()
{
    //Empty destructor
}

//Getters
string Client::getSurname()
{
    return this->surname; //gets last name
}

string Client::getForename()
{
    return this->forename; //gets first name
}