#include "BankingSystem.h"

static bool idExists = false;
static Client tempClient;
static BankAccount tempAccount;
static SavingsBankAccount tempSavingsAccount;

static int getClientCallBack(void *NotUsed, int argc, char **argv, char **azColName)
{
    tempClient.setName(argv[1]);
    tempClient.setAddress(argv[2]);
    tempClient.setPhoneNumber(argv[3]);
    if(strcmp(argv[6],"Basic") == 0)
    {
        tempAccount.setAccountID(argv[4]);
        tempAccount.setBalance(atof(argv[5]));
        tempAccount.setClient(tempClient);
        tempClient.setAccount(tempAccount);
    }
    else
    {
        tempSavingsAccount.setAccountID(argv[4]);
        tempSavingsAccount.setBalance(atof(argv[5]));
        tempSavingsAccount.setClient(tempClient);
        tempClient.setAccount(tempSavingsAccount);
    }
    return 0;

}
static int CheckIfIdExsits(void *NotUsed, int argc, char **argv, char **azColName) {
    // check if count is 0
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


int BankingApplication::displayMenu() {
    int choice;
    cout << "Welcome to FCAI Banking Application" << endl;
    cout << "Please choose one of the following options:" << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. List Clients and Accounts" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Deposit Money" << endl;
    cout << "5. Exit" << endl;
    cout << "Please Enter Choice =========> ";
    cin >> choice;
    while (choice < 1 || choice > 6) {
        cout << "Please enter a valid choice!" << endl;
        cin >> choice;
    }
    return choice;
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
        account.setClient(client);

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
        account.setClient(client);
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
            cout << "An " << "Saving" << " account was created with ID FCAI-" << client.getAccount().getAccountID() << " and Starting Balance "<< client.getAccount().getBalance() <<" L.E." << endl;
        sqlite3_close(db);
    }
}

void BankingApplication::displayAccounts() {
    // ------------------ Sql ------------------
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;
    const char *data = "Callback function called";
    rc = sqlite3_open("BankingSystem.db", &db);
    if (rc)
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
    //---------------------------------------------------------------------------------
    string selectquery = "SELECT * FROM MainTable;";
    sql = selectquery.c_str();
    cout << "Clients and Accounts in the bank are: " << endl << endl;
    rc = sqlite3_exec(db, sql, SelectCallBack, 0, &zErrMsg);
    if (rc != SQLITE_OK)
        cout << "SQL error: " << zErrMsg << endl;
    else
        cout << "Operation done successfully" << endl;
    sqlite3_close(db);
}

void BankingApplication::withdraw() {
    // ------------------ Sql ------------------
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *data = "Callback function called";
    rc = sqlite3_open("BankingSystem.db", &db);
    if (rc)
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
    //---------------------------------------------------------------------------------
    string id;
    cout << "Please Enter the Account ID =========> ";
    cin >> id;

    //CheckIfIdExsits
    string sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + id + "'";
    rc = sqlite3_exec(db, sl.c_str(), CheckIfIdExsits, 0, &zErrMsg);
    if(!idExists)
    {
        cout << "Id is Not Found" << endl;
        return;
    }

    string sql = "SELECT * FROM MainTable WHERE accountID ='" +id +"'";
    rc = sqlite3_exec(db, sql.c_str(), getClientCallBack, 0, &zErrMsg);
    if (rc != SQLITE_OK)
        cout << "Id is Not Found" << endl;
    else
        cout << "Operation done successfully" << endl;

    cout << "Please Enter the Amount you want to withdraw =========> ";
    int amount;
    cin >> amount;
    tempClient.getAccount().withdraw(amount);

    // ------------------ Sql ------------------
        string updatequery = "UPDATE MainTable SET balance = " + to_string(tempClient.getAccount().getBalance()) + " WHERE accountID = " + id + ";";
        rc = sqlite3_exec(db, updatequery.c_str(), SelectCallBack, 0, &zErrMsg);
        if (rc != SQLITE_OK)
            cout << "SQL error: " << zErrMsg << endl;
        sqlite3_close(db);
}
void BankingApplication::Deposit() {
    // ------------------ Sql ------------------
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *data = "Callback function called";
    rc = sqlite3_open("BankingSystem.db", &db);
    if (rc)
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
    //---------------------------------------------------------------------------------
    string id;
    cout << "Please Enter the Account ID =========> ";
    cin >> id;

    //CheckIfIdExsits
    string sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + id + "'";
    rc = sqlite3_exec(db, sl.c_str(), CheckIfIdExsits, 0, &zErrMsg);
    if(!idExists)
    {
        cout << "Id is Not Found" << endl;
        return;
    }
    string sql = "SELECT * FROM MainTable WHERE accountID ='" +id +"'";
    rc = sqlite3_exec(db, sql.c_str(), getClientCallBack, 0, &zErrMsg);
    if (rc != SQLITE_OK)
        cout << "SQL error: " << zErrMsg << endl;
    else
        cout << "Operation done successfully" << endl;

    cout << "Please Enter the Amount you want to Deposit =========> ";
    int amount;
    cin >> amount;
    tempClient.getAccount().deposit(amount);

    // ------------------ Sql ------------------
        string updatequery = "UPDATE MainTable SET balance = " + to_string(tempClient.getAccount().getBalance()) + " WHERE accountID = " + id + ";";
        rc = sqlite3_exec(db, updatequery.c_str(), SelectCallBack, 0, &zErrMsg);
        if (rc != SQLITE_OK)
            cout << "SQL error: " << zErrMsg << endl;
        sqlite3_close(db);
}

void BankingApplication::run() {
    int choice;
    do {
        choice = displayMenu();
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                displayAccounts();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                Deposit();
                break;
            case 5:
                cout << "Thank you for using our system" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 5);
}
