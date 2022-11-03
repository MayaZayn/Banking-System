#include "BankAccount.h"

BankAccount::BankAccount(double amountOfMoney) : balance(amountOfMoney), accountID(generateAccountID()) {}

string BankAccount::getAccountID() {
    return accountID;
}

double BankAccount::getBalance() {
    return balance;
}

void BankAccount::setAccountID(string accountID) {
    this->accountID = accountID;
}

void BankAccount::setBalance(double balance) {
    this->balance = balance;
}

void BankAccount::withdraw(double moneyToWithdraw) {
    if (balanceIsSufficient(moneyToWithdraw)) {
        balance -= moneyToWithdraw;
        cout << "New Balance: " << balance << endl;
    }
    else
        cout << "Sorry! Your Balance Is Not Sufficient.\n";
}

void BankAccount::deposit(double moneyToDeposit) {
    balance += moneyToDeposit;
    cout << "Money Deposited Successfully!\n";
    cout << "New Balance: " << balance << endl;
}

//While running in BankingApplication claas it should be checked whether the id generated exists or not
string BankAccount::generateAccountID() {
    srand(time(nullptr));
    rand() % (1000000000 - 100000000) + 100000000;
    string first = to_string(rand() % (1000 - 100) + 100),
           second = to_string(rand() % (1000 - 100) + 100),
           third = to_string(rand() % (1000 - 100) + 100), id = first + '-' + second + '-' + third;
    return id;
}

bool BankAccount::balanceIsSufficient(double moneyToWithdraw) {
    if (balance >= moneyToWithdraw) {
        return true;
    }
    return false;
}
