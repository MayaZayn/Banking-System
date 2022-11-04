#include "BankingSystem.h"

SavingsBankAccount::SavingsBankAccount() : minimumBalance(1000) {}

SavingsBankAccount::SavingsBankAccount(double balance) : minimumBalance(1000) {
    double tmpBalance = balance;
    tmpBalance = validateMoney(balance);
    while (tmpBalance < minimumBalance) {
        cout << "You can't create a Savings Account with less than 1000 LE as initial balance!\n";
        cin >> tmpBalance;
    }
    this->setBalance(tmpBalance);
    cout << "Your new Savings Account has been created with balance: " << this->getBalance() << endl;
    this->setAccountID(this->generateAccountID());
}

void SavingsBankAccount::setMinimumBalance(double minimumBalance) {
    double tmpMinimumBalance = BankAccount::validateMoney(minimumBalance);
    this->minimumBalance = tmpMinimumBalance;
}

double SavingsBankAccount::getMinimumBalance() {
    return minimumBalance;
}

void SavingsBankAccount::withdraw(double moneyToWithdraw) {
    double tmpMoneyToWithdraw = moneyToWithdraw, currentBalance = this->getBalance();
    tmpMoneyToWithdraw = validateMoney(moneyToWithdraw);
    while (currentBalance - tmpMoneyToWithdraw < minimumBalance) {
        cout << "Sorry! This is more than you can withdraw from your savings account.\n";
        cout << "Please enter the amount to withdraw:\n";
        cin >> tmpMoneyToWithdraw;
    }
    BankAccount::withdraw(tmpMoneyToWithdraw);
}

void SavingsBankAccount::deposit(double moneyToDeposit) {
    double tmpMoneyToDeposit = moneyToDeposit;
    tmpMoneyToDeposit = validateMoney(moneyToDeposit);
    while (tmpMoneyToDeposit < 100) {
        cout << "You can't deposit any amount of money less than 100 LE!\n";
        cout << "Please enter money to deposit:\n";
        cin >> tmpMoneyToDeposit;
    }
    BankAccount::deposit(tmpMoneyToDeposit);
}


