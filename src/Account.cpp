#include "Account.h"

namespace banking
{
    Account::Account()
        : id(0), balance(0)
    {
    }

    Account::Account(int id, const std::string& owner, double balance)
        : id(id), owner(owner), balance(balance)
    {
    }

    int Account::getId() const
    {
        return id;
    }

    const std::string& Account::getOwner() const
    {
        return owner;
    }

    double Account::getBalance() const
    {
        return balance;
    }

    void Account::deposit(double amount)
    {
        balance += amount;
    }

    void Account::withdraw(double amount)
    {
        balance -= amount;
    }
}
