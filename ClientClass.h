#ifndef BANK_CLIENTCLASS_H
#define BANK_CLIENTCLASS_H

#include <iostream>
#include <regex>
#include "BankAccount.h"

using namespace std;

class Client{
private:
    string name;
    string address;
    string phoneNumber;
    BankAccount* account;
    bool checkValidInput(string, char);
public:
    //Getters
    string getName();
    string getAddress();
    string getPhoneNumber();
    BankAccount* getAccount();

    //Setters
    void setName(string);
    void setAddress(string);
    void setPhoneNumber(string);
    void setAccount(BankAccount&);

    //Overload input operator
    friend istream& operator>> (istream&, Client&);

    //destructor
    ~Client();
};
#endif //BANK_CLIENTCLASS_H
