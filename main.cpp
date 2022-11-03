#include "BankAccount.h"
#include "SavingsBankAccount.h"

int main() {
    //Make sure the bankingApplication operates as in requested in the assignment
    //Why does this code cout the same account id for different objects??
    BankAccount x;
    cout << x.getAccountID() << endl;
    SavingsBankAccount y(1005);
    cout << y.getAccountID() << endl;
    x.deposit(199);
    x.withdraw(59);
    y.deposit(100);
    y.deposit(49);
    y.withdraw(1199);
    y.withdraw(1);
    return 0;
}
