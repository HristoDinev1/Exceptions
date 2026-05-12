#pragma once
#include <string>

namespace banking
{
    enum class TransactionType
    {
        Deposit,
        Withdraw,
        Transfer
    };

    class Transaction
    {
    private:
        TransactionType type;
        double amount;
        std::string description;

    public:
        Transaction();
        Transaction(TransactionType type, double amount, const std::string& description);

        double getAmount() const;
    };
}
