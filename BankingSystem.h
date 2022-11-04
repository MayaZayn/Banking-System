#ifndef MAIN_CPP_BANKINGSYSTEM_H
#define MAIN_CPP_BANKINGSYSTEM_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <regex>

using namespace std;

class Client;

class BankAccount {
private:
    string accountID;
    double balance;
    Client *client;
public:
    //Constructors
    BankAccount() : balance(0), accountID(generateAccountID()) {}
    explicit BankAccount(double);

    //Getters
    string getAccountID();
    double getBalance();
    Client getClient();

    //Setters
    void setAccountID(string);
    void setBalance(double);
    void setClient(Client);

    //Main Functions
    virtual void withdraw(double);
    virtual void deposit(double);

    //Additional Functions
    string generateAccountID();
    bool balanceIsSufficient(double);
    double validateMoney(double);

    //Overload operators >> & <<
    friend istream& operator>> (istream&, BankAccount&);
//    friend ostream& operator<< (ostream&, BankAccount&);

    //Destructor
    ~BankAccount();
};

class SavingsBankAccount : public BankAccount {
private:
    double minimumBalance;
public:
    //Constructors
    explicit SavingsBankAccount();
    explicit SavingsBankAccount(double balance);

    //Setter and Getter
    void setMinimumBalance(double);
    double getMinimumBalance();

    //Main Functions (overridden)
    void withdraw(double) override;
    void deposit(double) override;
};

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
    BankAccount getAccount();

    //Setters
    void setName(string);
    void setAddress(string);
    void setPhoneNumber(string);
    void setAccount(BankAccount&);

    //Overload input and output operators
    friend istream& operator>> (istream&, Client&);
//    friend ostream& operator<< (ostream&, const Client&);

    //destructor
    ~Client();
};
#endif //MAIN_CPP_BANKINGSYSTEM_H
