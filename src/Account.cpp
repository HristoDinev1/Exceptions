#include "Account.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Account::Account()
    : id(0), ownerName(""), balance(0.0) {}

Account::Account(int id, const MyString& ownerName, double initialBalance)
    : id(id), ownerName(ownerName), balance(initialBalance) {}

int             Account::getId()        const { return id; }
const MyString& Account::getOwnerName() const { return ownerName; }
double          Account::getBalance()   const { return balance; }
const MyVector<Transaction>& Account::getHistory() const { return history; }

void Account::deposit(double amount) {
    if (amount < 0)
        throw std::invalid_argument("deposit: amount must be non-negative");
    if (std::isinf(balance + amount))
        throw std::overflow_error("deposit: amount would overflow balance");
    balance += amount;
    history.push_back(Transaction(TransactionType::Deposit, amount));
}

void Account::withdraw(double amount) {
    if (amount < 0)
        throw std::invalid_argument("withdraw: amount must be non-negative");
    if (amount > balance)
        throw std::underflow_error("withdraw: insufficient funds");
    balance -= amount;
    history.push_back(Transaction(TransactionType::Withdraw, amount));
}

void Account::recordTransfer(double amount, int otherAccountId, bool incoming) {
    if (incoming) {
        balance += amount;
        history.push_back(Transaction(TransactionType::TransferIn,  amount, otherAccountId));
    } else {
        balance -= amount;
        history.push_back(Transaction(TransactionType::TransferOut, amount, otherAccountId));
    }
}

void Account::printSummary() const {
    std::cout << "Account #" << id
              << " | Owner: " << ownerName
              << " | Balance: " << balance << '\n';
}

void Account::printHistory() const {
    std::cout << "History for account #" << id << ":\n";
    for (std::size_t i = 0; i < history.size(); ++i) {
        std::cout << "  ";
        history[i].print();
    }
}
