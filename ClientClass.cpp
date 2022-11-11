#include "BankingSystem.h"

/***Setters and Getters***/
string Client::getName(){
    return name;
}

string Client::getAddress(){
    return address;
}

string Client::getPhoneNumber(){
    return phoneNumber;
}

BankAccount Client::getAccount() {
    return (*account);
}

void Client:: setName(string name){
    this->name = name;
}

void Client:: setAddress(string address){
    this->address = address;
}

void Client:: setPhoneNumber(string number){
    this->phoneNumber = number;
}

void Client:: setAccount(BankAccount& account){
    this-> account = new BankAccount;
    *(this->account) = account;
}

//Overload the input operator
istream& operator>> (istream& in, Client& client){
    cout << "Hello, Please Enter The Information Below: " << endl;

    // Get user's name
    cout << "Enter your name :" << endl;
    getline(in >> ws, client.name);
    while (!client.checkValidInput(client.name, 'n')){
        cout << "Please enter a valid Name!" << endl;
        getline(in >> ws, client.name);
    }

    // Get user's address
    cout << "Enter your address :" << endl;
    getline(in >> ws, client.address); // to validate somehow

    // Get user's phone number
    cout << "Enter your phone number :" << endl;
    getline(in >> ws, client.phoneNumber);
    while (!client.checkValidInput(client.phoneNumber, 'p')){
        cout << "Please enter a valid Phone number!" << endl;
        getline(in >> ws, client.phoneNumber);
    }

    return in;
}

// Validate input
bool Client:: checkValidInput(string input, char inputType){
    if (inputType == 'n'){
        regex match("[aA-zZ' ']*");
        return regex_match(input,match);
    } else {
        regex match("(01)(1|2|0|5)[0-9]{8}");
        return regex_match(input, match);
    }
}

Client:: ~Client() {
    account = nullptr;
    delete account;
}