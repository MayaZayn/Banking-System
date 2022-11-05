#include "BankingSystem.h"



int main() {
    //Make sure the bankingApplication operates as in requested in the assignment
    //Why does this code cout the same account id for different objects?? Although it works fine with the debugger!
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char *sql;
    const char* data = "Callback function called";
    rc = sqlite3_open("BankingSystem.db", &db);
    if(rc)
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
    else
        cout << "Opened database successfully" << endl;
    //Create SQL statement

    //insert SQL query
    string ID = "Ahmed";
    string sl = "SELECT Count(*) As n FROM MainTable where accountID = '" + ID + "';";
    rc = sqlite3_exec(db, sl.c_str(), callback, (void*)data, &zErrMsg);
    if(rc)
        cout << "SQL error: " << zErrMsg << endl;
    else
        cout << "Operation done successfully" << endl;



}


