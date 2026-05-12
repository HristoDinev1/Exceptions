#pragma once
#include "Account.h"
#include "MyVector.h"

namespace banking
{
    class BankSystem
    {
    private:
        MyVector<Account> accounts;

    public:
        void createAccount(int id, const std::string& owner, double balance);
        void deposit(int id, double amount);
        void withdraw(int id, double amount);

        Account& findAccount(int id);
        void printAccounts() const;
    };
}
