#pragma once
#include "Account.h"
#include "MyVector.h"
#include "MyString.h"

class BankSystem {
private:
    MyVector<Account> accounts;

public:
    BankSystem();

    void createAccount(int id, const MyString& ownerName, double initialBalance);
    void deposit (int accountId, double amount);
    void withdraw(int accountId, double amount);
    void transfer(int fromId, int toId, double amount);

    Account&       findAccount(int accountId);
    const Account& findAccount(int accountId) const;
    int            findAccountIndex(int accountId) const;

    void sortById();
    void sortByBalance();

    const MyVector<Account>& getAccounts() const;
    MyVector<Account>&       getAccounts();
    std::size_t              getAccountCount() const;

    void printAllAccounts() const;
};
