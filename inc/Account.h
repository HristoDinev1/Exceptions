#pragma once
#include "MyString.h"
#include "MyVector.h"
#include "Transaction.h"

class Account {
private:
    int id;
    MyString ownerName;
    double balance;
    MyVector<Transaction> history;

public:
    Account();
    Account(int id, const MyString& ownerName, double initialBalance = 0.0);

    int             getId()        const;
    const MyString& getOwnerName() const;
    double          getBalance()   const;
    const MyVector<Transaction>& getHistory() const;

    void deposit(double amount);
    void withdraw(double amount);
    void recordTransfer(double amount, int otherAccountId, bool incoming);

    void printSummary() const;
    void printHistory() const;
};
