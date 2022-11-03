#ifndef MAIN_CPP_SAVINGSBANKACCOUNT_H
#define MAIN_CPP_SAVINGSBANKACCOUNT_H

#include "BankAccount.h"


class SavingsBankAccount : public BankAccount {
private:
    double minimumBalance;
public:
    //Shall there be a default constructor???
    //Constructor
    explicit SavingsBankAccount(double balance);

    //Setter and Getter
    void setMinimumBalance(double);
    double getMinimumBalance();

    //Main Functions (overridden)
    void withdraw(double) override;
    void deposit(double) override;
};


#endif
