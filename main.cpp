#include "BankingSystem.h"



int main() {
    //Make sure the bankingApplication operates as in requested in the assignment
    //Why does this code cout the same account id for different objects?? Although it works fine with the debugger!
    //I Dont know But i will know soon isa
    //BankAccount account1(1000);
    // create MainTable table in the database
//    sqlite3 *db;
//    char *zErrMsg = 0;
//    int rc;
//    const char *sql;
//    const char *data = "Callback function called";
//    rc = sqlite3_open("BankingSystem.db", &db);
//    if (rc)
//        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
//    else
//        cout << "Opened database successfully" << endl;
//    sql = "CREATE TABLE IF NOT EXISTS MainTable(" \
//        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
//        "name TEXT NOT NULL," \
//        "address TEXT NOT NULL," \
//        "phoneNumber TEXT NOT NULL," \
//        "accountID INTEGER NOT NULL," \
//        "balance REAL NOT NULL," \
//        "accountType TEXT NOT NULL);";
//    rc = sqlite3_exec(db, sql, SelectCallBack, 0, &zErrMsg);
//    if (rc != SQLITE_OK) {
//        cout << "SQL error: " << zErrMsg << endl;
//        sqlite3_free(zErrMsg);
//    }
//    else
//        cout << "Table created successfully" << endl;
BankingApplication bankingApplication;
bankingApplication.createAccount();
}


//CREATE TABLE IF NOT EXISTS MainTable(
//    id INTEGER PRIMARY KEY AUTOINCREMENT,
//    name TEXT NOT NULL,
//    address TEXT NOT NULL,
//    phoneNumner TEXT NOT NULL,
//    accountID INTEGER NOT NULL,
//    balance REAL NOT NULL,
//    accountType TEXT NOT NULL
//);

