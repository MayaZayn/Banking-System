#include "BankingSystem.h"

BankAccount::BankAccount(double amountOfMoney) : balance(validateMoney(amountOfMoney)), accountID(generateAccountID()) {}

string BankAccount::getAccountID() {
    return this->accountID;
}

double BankAccount::getBalance() {
    return balance;
}

Client BankAccount::getClient() {
    return (*client);
}

void BankAccount::setAccountID(string accountID) {
    this->accountID = accountID;
}

void BankAccount::setBalance(double balance) {
    this->balance = validateMoney(balance);
}

void BankAccount::setClient(Client client) {
    this->client = new Client;
    *(this->client) = client;
}

void BankAccount::withdraw(double moneyToWithdraw) {
    double tmpMoneyToWithdraw = validateMoney(moneyToWithdraw);
    if (balanceIsSufficient(tmpMoneyToWithdraw)) {
        this -> balance -= tmpMoneyToWithdraw;
        cout << "Account ID: " << accountID << endl;
        cout << "New Balance: " << balance << endl;
    }
    else
        cout << "Sorry! Your Balance Is Not Sufficient.\n";
}

void BankAccount::deposit(double moneyToDeposit) {
    double tmpMoneyToDeposit = validateMoney(moneyToDeposit);
    balance += tmpMoneyToDeposit;
    cout << "Money Deposited Successfully!\n";
    cout << "New Balance: " << balance << endl;
}

//While running in BankingApplication class it should be checked whether the id generated exists or not
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

double BankAccount::validateMoney(double balance) {
    string tmpBalance = to_string(balance);
    bool valid = true;
    for (char & digit : tmpBalance) {
        if (!isdigit(digit) && digit != '.') {
            valid = false;
            break;
        }
    }
    while (!valid) {
        cout << "Please make sure to enter only numbers!\n";
        valid = true;
        cin >> tmpBalance;
        for (char & digit : tmpBalance) {
            if (!isdigit(digit) && digit != '.') {
                valid = false;
                break;
            }
        }
    }
    return stod(tmpBalance);
}

istream& operator>>(istream &in, BankAccount &account) {
    cout << "Please enter an account ID:\n";
    string id; cin >> id;
    account.setAccountID(id);
    cout << "Please enter the balance:\n";
    double balance; cin >> balance;
    account.setBalance(balance);
    return in;
}

BankAccount::~BankAccount() {
    //There is a memory leak here
    client = nullptr;
    delete client;
}

