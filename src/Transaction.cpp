#include "Transaction.h"

namespace banking
{
    Transaction::Transaction()
        : type(TransactionType::Deposit), amount(0)
    {
    }

    Transaction::Transaction(TransactionType type, double amount, const std::string& description)
        : type(type), amount(amount), description(description)
    {
    }

    double Transaction::getAmount() const
    {
        return amount;
    }
}
