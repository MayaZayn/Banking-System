#ifndef MAIN_CPP_BANKACCOUNT_H
#define MAIN_CPP_BANKACCOUNT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

class BankAccount {
    // Overload insertion and extraction operators in this class and the derived one (or just this one)
private:
    string accountID; //Shall this be string or not?
    double balance;
    //Client *client;
public:
    //Validate Input in each step

    //Constructors
    BankAccount() : balance(0), accountID(generateAccountID()) {}
    explicit BankAccount(double);

    //Getters
    string getAccountID();
    double getBalance();
//    Client getClient();

    //Setters
    void setAccountID(string);
    void setBalance(double);
//    void setClient(Client);

    //Main Functions
    virtual void withdraw(double);
    virtual void deposit(double);

    //Additional Functions
    string generateAccountID();
    bool balanceIsSufficient(double);
};

#endif
