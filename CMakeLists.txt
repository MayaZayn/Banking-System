cmake_minimum_required(VERSION 3.22)
project(Banking_System)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(sqlite)

add_executable(Banking_System
        sqlite/sqlite3.c
        sqlite/sqlite3.h
        BankAccount.cpp
        BankingApplication.cpp
        BankingSystem.h
        ClientClass.cpp
        main.cpp
        SavingsBankAccount.cpp)
