#pragma once
#include <string>
#include "MyVector.h"
#include "Transaction.h"

namespace banking
{
    class Account
    {
    private:
        int id;
        std::string owner;
        double balance;
        MyVector<Transaction> history;

    public:
        Account();
        Account(int id, const std::string& owner, double balance);

        int getId() const;
        const std::string& getOwner() const;
        double getBalance() const;

        void deposit(double amount);
        void withdraw(double amount);
    };
}
