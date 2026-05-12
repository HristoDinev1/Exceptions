#include "BankSystem.h"
#include <iostream>

namespace banking
{
    void BankSystem::createAccount(int id, const std::string& owner, double balance)
    {
        accounts.pushBack(Account(id, owner, balance));
    }

    void BankSystem::deposit(int id, double amount)
    {
        findAccount(id).deposit(amount);
    }

    void BankSystem::withdraw(int id, double amount)
    {
        findAccount(id).withdraw(amount);
    }

    Account& BankSystem::findAccount(int id)
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getId() == id)
            {
                return accounts[i];
            }
        }

        return accounts[0];
    }

    void BankSystem::printAccounts() const
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            std::cout << accounts[i].getId() << " "
                      << accounts[i].getOwner() << " "
                      << accounts[i].getBalance() << '\n';
        }
    }
}
