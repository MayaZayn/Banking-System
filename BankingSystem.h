#ifndef MAIN_CPP_BANKINGSYSTEM_H
#define MAIN_CPP_BANKINGSYSTEM_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <regex>
#include "sqlite/sqlite3.h"

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

    //Overload operator >>
    friend istream& operator>> (istream&, BankAccount&);

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

    //Overload input operator
    friend istream& operator>> (istream&, Client&);

    //destructor
    ~Client();
};

class BankingApplication {
public:
    // Main Functions
    int displayMenu();
    void createAccount();
    void displayAccounts();
    void withdraw();
    void Deposit();
    void run();
};


// Sql Functions
// callback function for sql
static int SelectCallBack(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    cout << "------------------" << argv[1] << "------------------" << endl;
    cout << "Address: " << argv[2] << " ," << "Phone Number: " << argv[3] << endl;
    cout << "Account ID: " << argv[4] << " (" << argv[6] << ")" << endl;
    cout << "Balance:" << argv[5] << endl;
    cout << endl;
    return 0;
}
#endif //MAIN_CPP_BANKINGSYSTEM_H
