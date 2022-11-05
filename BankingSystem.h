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
private:
    int choice;
public:
    // Main Functions
    void displayMenu();
    void createAccount();
};


// Sql Functions
// callback function for sql
static int Printcallback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

static int CheckIfIdExsits(void *NotUsed, int argc, char **argv, char **azColName, bool& found) {
    if(strcmp(argv[0] , "0") == 0)
    {
        found = false;
    }
    else
    {
        found = true;
    }
}
//
//void SelectFromTable(string SelectQuery)
//{
//    sqlite3 *db;
//    char *zErrMsg = 0;
//    int rc;
//    const char *sql;
//    const char* data = "Callback function called";
//
//    /* Open database */
//    rc = sqlite3_open("BankingSystem.db", &db);
//    if (rc)
//        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
//    else
//        cout << "Opened database successfully" << endl;
//
//    /* Create SQL statement */
//    sql = SelectQuery.c_str();
//
//    /* Execute SQL statement */
//    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
//    if (rc != SQLITE_OK) {
//        cout << "SQL error: " << zErrMsg << endl;
//        sqlite3_free(zErrMsg);
//    } else {
//        cout << "Operation done successfully" << endl;
//    }
//    sqlite3_close(db);
//}


#endif //MAIN_CPP_BANKINGSYSTEM_H
