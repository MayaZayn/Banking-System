#include "BankingSystem.h"

int main() {
    //Make sure the bankingApplication operates as in requested in the assignment
    //Why does this code cout the same account id for different objects?? Although it works fine with the debugger!
    BankAccount x;
    cout << x.getAccountID() << endl;
    SavingsBankAccount y(1005);
    cout << y.getAccountID() << endl;
    Client client;
    x.setClient(client);
    y.setClient(client);
    client.setAccount(y);
    x.deposit(199);
    x.withdraw(59);
    y.deposit(100);
    y.deposit(49);
    y.withdraw(1199);
    y.withdraw(1);
    return 0;
}
