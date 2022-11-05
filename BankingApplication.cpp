#include "BankingSystem.h"

static bool idExists = false;

static int CheckIfIdExsits(void *NotUsed, int argc, char **argv, char **azColName) {
    if(strcmp(argv[0] , "0") == 0)
    {
        idExists = false;
    }
    else
    {
        idExists = true;
    }
    return 0;
}

void BankingApplication::displayMenu() {
    int choice;
    cout << "Welcome to FCAI Banking Application" << endl;
    cout << "Please choose one of the following options:" << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. List Clients and Accounts" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Deposit Money" << endl;
    cout << "Please Enter Choice =========> ";
    cin >> choice;
    while (choice < 1 || choice > 5) {
        cout << "Please enter a valid choice!" << endl;
        cin >> choice;
    }
    this->choice = choice;
}

void BankingApplication::createAccount() {
    Client client;
    cin >> client;
    cout << "Account Created Successfully!" << endl;
    cout << "Client Name: " << client.getName() << endl;
    cout << "Client Address: " << client.getAddress() << endl;
    cout << "Client Phone Number: " << client.getPhoneNumber() << endl;
    int BankAccountType;
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =========> ";
    cin >> BankAccountType;
    while (BankAccountType < 1 || BankAccountType > 2) {
        cout << "Please enter a valid choice!" << endl;
        cin >> BankAccountType;
    }
    if(BankAccountType == 1) {
        // ------------------ Sql ------------------
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char *sql;
        const char *data = "Callback function called";
        rc = sqlite3_open("BankingSystem.db", &db);
        if (rc)
            cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        else
            cout << "Opened database successfully" << endl;
        //---------------------------------------------------------------------------------

        BankAccount account;
        int StartingBalance;
        cout << "Please Enter the Starting Balance =========> ";
        cin >> StartingBalance;
        account.setBalance(StartingBalance);
        string id = account.generateAccountID();
        // check if id exists in database
        string sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + id + "';";
        rc = sqlite3_exec(db, sl.c_str(), CheckIfIdExsits, (void *) data, &zErrMsg);
        while(idExists)
        {
            id = account.generateAccountID();
            // check if id exists in database
            sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + id + "';";
            rc = sqlite3_exec(db, sl.c_str(), CheckIfIdExsits, (void *) data, &zErrMsg);
        }
        account.setAccountID(id);
        if (rc)
            cout << "SQL error: " << zErrMsg << endl;
        else
            cout << "Operation done successfully" << endl;
        client.setAccount(account);

        // ------------------ Sql ------------------
        //insert Account and client into the database
        string Insertquery =
                "INSERT INTO MainTable (accountID, accountType, balance, name, address, phoneNumber) VALUES ('" +
                client.getAccount().getAccountID() + "', '" + "Basic" + "', '" +
                to_string(client.getAccount().getBalance()) + "', '" + client.getName() + "', '" + client.getAddress() +
                "', '" + client.getPhoneNumber() + "');";
        sql = Insertquery.c_str();
        rc = sqlite3_exec(db, sql, SelectCallBack, 0, &zErrMsg);
        if (rc != SQLITE_OK)
            cout << "SQL error: " << zErrMsg << endl;
        else
            cout << "An " << "Basic" << " account was created with ID FCAI-" << client.getAccount().getAccountID() << " and Starting Balance "<< client.getAccount().getBalance() <<" L.E." << endl;
        sqlite3_close(db);
    }
    else if(BankAccountType == 2) {
        // ------------------ Sql ------------------
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char *sql;
        const char *data = "Callback function called";
        rc = sqlite3_open("BankingSystem.db", &db);
        if (rc)
            cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        else
            cout << "Opened database successfully" << endl;
        //---------------------------------------------------------------------------------

        int StartingBalance;
        cout << "Please Enter the Starting Balance =========> ";
        cin >> StartingBalance;
        SavingsBankAccount account(StartingBalance);
        client.setAccount(account);
        string id = account.generateAccountID();
        // check if id exists in database
        string sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + id + "';";
        rc = sqlite3_exec(db, sl.c_str(), CheckIfIdExsits, (void *) data, &zErrMsg);
        while(idExists)
        {
            id = account.generateAccountID();
            // check if id exists in database
            sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + id + "';";
            rc = sqlite3_exec(db, sl.c_str(), CheckIfIdExsits, (void *) data, &zErrMsg);
        }
        account.setAccountID(id);
        // ------------------ Sql ------------------
        //insert Account and client into the database
        string Insertquery =
                "INSERT INTO MainTable (accountID, accountType, balance, name, address, phoneNumber) VALUES ('" +
                client.getAccount().getAccountID() + "', '" + "Saving" + "', '" +
                to_string(client.getAccount().getBalance()) + "', '" + client.getName() + "', '" + client.getAddress() +
                "', '" + client.getPhoneNumber() + "');";
        sql = Insertquery.c_str();
        // callbak function
        rc = sqlite3_exec(db, sql, SelectCallBack, 0, &zErrMsg);
        if (rc != SQLITE_OK)
            cout << "SQL error: " << zErrMsg << endl;
        else
            string selectquery = "SELECT FROM MainTable;";
        cout << "An " << "Saving" << " account was created with ID FCAI-" << client.getAccount().getAccountID() << " and Starting Balance "<< client.getAccount().getBalance() <<" L.E." << endl;
        sqlite3_close(db);
    }
}


//
//    cout << "Welcome to the Banking Application!" << endl;
//    cout << "Please enter your name: " << endl;
//    cin.ignore();
//    getline(cin, name);
//    while (!checkValidInput(name, 'n')) {
//        cout << "Please enter a valid Name!" << endl;
//        getline(cin, name);
//    }
//    cout << "Hello " << name << "!" << endl;
//    cout << "Please enter your address: " << endl;
//    getline(cin, address);
//    cout << "Please enter your phone number: " << endl;
//    getline(cin, phoneNumber);
//    while (!checkValidInput(phoneNumber, 'p')) {
//        cout << "Please enter a valid Phone number!" << endl;
//        getline(cin, phoneNumber);
//    }
//    cout << "Please enter the amount of money you want to deposit: " << endl;
//    cin >> amountOfMoney;
//    while (!checkValidInput(to_string(amountOfMoney), 'm')) {
//        cout << "Please enter a valid amount of money!" << endl;
//        cin >> amountOfMoney;
//    }
//    BankAccount account(amountOfMoney);
//    Client client;
//    client.setName(name);
//    client.setAddress(address);
//    client.setPhoneNumber(phoneNumber);
//    client.setAccount(account);
//    account.setClient(client);
//    cout << "Your account has been created successfully!" << endl;
//    cout << "Your account ID is: " << account.getAccountID() << endl;
//    cout << "Your balance is: " << account.getBalance() << endl;
//    cout << "Please enter the amount of money you want to withdraw: " << endl;
//    cin >> amountOfMoney;
//    while (!checkValidInput(to_string(amountOfMoney), 'm')) {
//        cout << "Please enter a valid amount of money!" << endl;
//        cin >> amountOfMoney;
//    }
//    account.withdraw(amountOfMoney);
//    cout << "Your balance is: " << account.getBalance() << endl;
//    cout << "Please enter the amount of money you want to deposit: " << endl;
//    cin >> amountOfMoney;
//    while (!checkValidInput(to_string(amountOfMoney), 'm')) {
//        cout << "Please enter a valid amount of money!" << endl;
//        cin >> amountOfMoney;
//    }
//    account.deposit(amountOfMoney);
//    cout << "Your balance is: " << account.getBalance() << endl;