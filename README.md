# Banking-System
 
***We Modeled, Designed and Developed a Banking Application..***    

**Made by:** [***Osama Maher***](https://github.com/osama392maher) -
[***Maya Ayman***](https://github.com/MayaZayn) -
[***Rawan Abdel-Rahman***](https://github.com/Rawanyounis123)     
**Requested by:** *Dr. Mohammed El-Ramly* in Object Oriented Programming course (Assingment 2)

## The System is divided into 4 classes:   
* **Client Class:**   
It holds the basic information of a client like his name, address and phone number. It holds a pointer to his bank account.
* **BankAccount Class:**  
It holds the accountID, the balance in the account and a pointer to the account's client
* **SavingBankAccoun Class:**  
It's a BankAccount but has more restrictions when client withdraws and deposits and it has minimum balance
* **BankingApplication Class:**  
This is the main class that runs the application. This class displays the main menu and accepts the user's choice. It maintains the DataBase that stores the accounts and clients Data. 
* This System has a DataBase Written in sqlite3 that stores the clients data and their accounts.

BankingApplication allows the user (the bank employee) to perform operations on a bank account:
* Create a bank account for a specific client
* List all the available bank accounts
* For each account, it allows him to display the account details, withdraw money and deposit money 
 ## The Class Diagram
<img src="https://user-images.githubusercontent.com/47755776/204836967-400c5a71-2bce-4cfb-9209-5398ecd49ac6.jpg" alt="UML Class Diagram" width="800"/>

## The Goal of this project is to:
* Practice Object-Oriented-Programming concepts using C++ (Inheritance - Composition - Encapsulation - Abstraction - etc..) 
* Practice building systems using OOP modeling and design with C++
* Practice working in a team and integrating the code together to come up with a final working program
