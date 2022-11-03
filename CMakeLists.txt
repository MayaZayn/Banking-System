cmake_minimum_required(VERSION 3.22)
project(Bank)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bank main.cpp BankAccount.cpp BankAccount.h SavingsBankAccount.cpp SavingsBankAccount.h)
