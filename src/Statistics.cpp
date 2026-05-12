#include "Statistics.h"
#include <iostream>

double Statistics::totalMoney(const BankSystem& bank) {
    double total = 0.0;
    const MyVector<Account>& accounts = bank.getAccounts();
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        total += accounts[i].getBalance();
    }
    return total;
}

double Statistics::averageBalance(const BankSystem& bank) {
    // No empty-check: division by zero if there are no accounts.
    return totalMoney(bank) / static_cast<double>(bank.getAccountCount());
}

Account Statistics::richestAccount(const BankSystem& bank) {
    const MyVector<Account>& accounts = bank.getAccounts();
    // Trusts that the bank has at least one account.
    std::size_t richestIdx = 0;
    for (std::size_t i = 1; i < accounts.size(); ++i) {
        if (accounts[i].getBalance() > accounts[richestIdx].getBalance()) {
            richestIdx = i;
        }
    }
    return accounts[richestIdx];
}

void Statistics::printStatistics(const BankSystem& bank) {
    std::cout << "=== Statistics ===\n";
    std::cout << "Total money:     " << totalMoney(bank) << '\n';
    std::cout << "Average balance: " << averageBalance(bank) << '\n';
    std::cout << "Richest:         ";
    Account r = richestAccount(bank);
    r.printSummary();
}
