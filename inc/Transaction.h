#pragma once
#include "MyString.h"

enum class TransactionType {
    Deposit,
    Withdraw,
    TransferIn,
    TransferOut
};

class Transaction {
private:
    TransactionType type;
    double amount;
    int otherAccountId;   // -1 if not a transfer

public:
    Transaction();
    Transaction(TransactionType type, double amount, int otherAccountId = -1);

    TransactionType getType() const;
    double getAmount() const;
    int getOtherAccountId() const;

    MyString typeAsString() const;

    void print() const;
};
