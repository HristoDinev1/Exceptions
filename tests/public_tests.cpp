#include <cassert>
#include <fstream>
#include "BankSystem.h"
#include "Statistics.h"
#include "MyVector.h"

using namespace banking;

void testDuplicateAccounts()
{
    BankSystem bank;

    bank.createAccount(1, "Ivan", 100);
    bank.createAccount(1, "Ivan2", 200);

    // Students should later prevent duplicate IDs
    assert(true);
}

void testNegativeDeposit()
{
    BankSystem bank;

    bank.createAccount(1, "Ivan", 100);
    bank.deposit(1, -500);

    // Should later throw invalid_argument
    assert(bank.findAccount(1).getBalance() == -400);
}

void testHugeWithdraw()
{
    BankSystem bank;

    bank.createAccount(1, "Ivan", 100);
    bank.withdraw(1, 1000000);

    // Should later prevent impossible balances
    assert(bank.findAccount(1).getBalance() < 0);
}

void testInvalidAccountLookup()
{
    BankSystem bank;

    bank.createAccount(1, "Ivan", 100);

    // Currently unsafe
    bank.findAccount(999);
}

void testEmptyStatistics()
{
    MyVector<Account> accounts;

    // Students should later protect this
    Statistics::averageBalance(accounts);
}

void testUnsafeVectorAccess()
{
    MyVector<int> values;

    values.pushBack(5);

    // Should later throw out_of_range
    values[50] = 100;
}

void testMalformedFile()
{
    std::ofstream out("broken.txt");
    out << "not,a,valid,file\n";
    out.close();

    // Students should later validate parsing
    assert(true);
}

void testWhitespaceNames()
{
    BankSystem bank;

    bank.createAccount(1, "   ", 500);

    // Should later reject whitespace-only names
    assert(bank.findAccount(1).getOwner() == "   ");
}

void testTransferToMissingAccount()
{
    BankSystem bank;

    bank.createAccount(1, "Ivan", 100);

    // Future robustness target
    bank.findAccount(999);
}

int main()
{
    testDuplicateAccounts();
    testNegativeDeposit();
    testHugeWithdraw();
    testInvalidAccountLookup();
    testEmptyStatistics();
    testUnsafeVectorAccess();
    testMalformedFile();
    testWhitespaceNames();
    testTransferToMissingAccount();

    return 0;
}
