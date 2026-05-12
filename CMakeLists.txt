cmake_minimum_required(VERSION 3.16)
project(BankSystem)

set(CMAKE_CXX_STANDARD 23)

include_directories(inc)

add_executable(BankSystem
    src/main.cpp
    src/Application.cpp
    src/Menu.cpp
    src/BankSystem.cpp
    src/Account.cpp
    src/Transaction.cpp
)