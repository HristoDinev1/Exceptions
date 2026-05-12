#pragma once
#include "BankSystem.h"

class Statistics {
public:
    static double  totalMoney(const BankSystem& bank);
    static double  averageBalance(const BankSystem& bank);
    static Account richestAccount(const BankSystem& bank);

    static void printStatistics(const BankSystem& bank);
};
