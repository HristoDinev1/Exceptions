#include "Transaction.h"
#include <iostream>

Transaction::Transaction()
    : type(TransactionType::Deposit), amount(0.0), otherAccountId(-1) {}

Transaction::Transaction(TransactionType type, double amount, int otherAccountId)
    : type(type), amount(amount), otherAccountId(otherAccountId) {}

TransactionType Transaction::getType()   const { return type; }
double          Transaction::getAmount() const { return amount; }
int             Transaction::getOtherAccountId() const { return otherAccountId; }

MyString Transaction::typeAsString() const {
    switch (type) {
        case TransactionType::Deposit:     return MyString("Deposit");
        case TransactionType::Withdraw:    return MyString("Withdraw");
        case TransactionType::TransferIn:  return MyString("TransferIn");
        case TransactionType::TransferOut: return MyString("TransferOut");
    }
    return MyString("Unknown");
}

void Transaction::print() const {
    std::cout << typeAsString() << " " << amount;
    if (otherAccountId != -1) {
        std::cout << " (acc " << otherAccountId << ")";
    }
    std::cout << '\n';
}
