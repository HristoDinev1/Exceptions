#include "BankSystem.h"
#include <iostream>

BankSystem::BankSystem() {}

void BankSystem::createAccount(int id, const MyString& ownerName, double initialBalance) {
    Account account(id, ownerName, initialBalance);
    accounts.push_back(account);
}

void BankSystem::deposit(int accountId, double amount) {
    Account& account = findAccount(accountId);
    account.deposit(amount);
}

void BankSystem::withdraw(int accountId, double amount) {
    Account& account = findAccount(accountId);
    account.withdraw(amount);
}

void BankSystem::transfer(int fromId, int toId, double amount) {
    Account& from = findAccount(fromId);
    Account& to   = findAccount(toId);
    from.recordTransfer(amount, toId,   false);
    to.recordTransfer  (amount, fromId, true);
}

int BankSystem::findAccountIndex(int accountId) const {
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getId() == accountId) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

Account& BankSystem::findAccount(int accountId) {
    int idx = findAccountIndex(accountId);
    return accounts[idx];
}

const Account& BankSystem::findAccount(int accountId) const {
    int idx = findAccountIndex(accountId);
    return accounts[idx];
}

void BankSystem::sortById() {
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        for (std::size_t j = 0; j + 1 < accounts.size() - i; ++j) {
            if (accounts[j].getId() > accounts[j + 1].getId()) {
                Account tmp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tmp;
            }
        }
    }
}

void BankSystem::sortByBalance() {
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        for (std::size_t j = 0; j + 1 < accounts.size() - i; ++j) {
            if (accounts[j].getBalance() > accounts[j + 1].getBalance()) {
                Account tmp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = tmp;
            }
        }
    }
}

const MyVector<Account>& BankSystem::getAccounts() const { return accounts; }
MyVector<Account>&       BankSystem::getAccounts()       { return accounts; }
std::size_t              BankSystem::getAccountCount() const { return accounts.size(); }

void BankSystem::printAllAccounts() const {
    std::cout << "=== All accounts ===\n";
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        accounts[i].printSummary();
    }
}
