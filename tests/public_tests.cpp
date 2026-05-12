#include <catch2/catch_test_macros.hpp>

#include "BankSystem.h"
#include "Account.h"
#include "MyVector.h"
#include "MyString.h"
#include "Statistics.h"
#include "Transaction.h"

TEST_CASE("Create account and check balance") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE(bank.getAccountCount() == 1);
    REQUIRE(bank.findAccount(1).getBalance() == 100.0);
    REQUIRE(bank.findAccount(1).getOwnerName() == MyString("Alice"));
}

TEST_CASE("Deposit increases balance") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    bank.deposit(1, 50.0);
    REQUIRE(bank.findAccount(1).getBalance() == 150.0);
}

TEST_CASE("Withdraw decreases balance") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    bank.withdraw(1, 30.0);
    REQUIRE(bank.findAccount(1).getBalance() == 70.0);
}

TEST_CASE("Transfer moves money between accounts") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    bank.createAccount(2, MyString("Bob"),   50.0);
    bank.transfer(1, 2, 30.0);
    REQUIRE(bank.findAccount(1).getBalance() == 70.0);
    REQUIRE(bank.findAccount(2).getBalance() == 80.0);
}

TEST_CASE("Transaction history is recorded") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    bank.deposit(1, 50.0);
    bank.withdraw(1, 20.0);
    REQUIRE(bank.findAccount(1).getHistory().size() == 2);
    REQUIRE(bank.findAccount(1).getHistory()[0].getType() == TransactionType::Deposit);
    REQUIRE(bank.findAccount(1).getHistory()[1].getType() == TransactionType::Withdraw);
}

TEST_CASE("MyVector basic operations") {
    MyVector<int> v;
    REQUIRE(v.empty());
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[2] == 3);
}

TEST_CASE("MyVector grows beyond initial capacity") {
    MyVector<int> v;
    for (int i = 0; i < 100; ++i) v.push_back(i);
    REQUIRE(v.size() == 100);
    REQUIRE(v[99] == 99);
}

TEST_CASE("MyString basic operations") {
    MyString s("Hello");
    REQUIRE(s.size() == 5);
    REQUIRE(s == MyString("Hello"));

    MyString other = s;
    REQUIRE(other == s);

    other += MyString(" World");
    REQUIRE(other == MyString("Hello World"));
    REQUIRE(s == MyString("Hello"));   // s is untouched
}

TEST_CASE("Statistics work for a non-empty bank") {
    BankSystem bank;
    bank.createAccount(1, MyString("A"), 100.0);
    bank.createAccount(2, MyString("B"), 200.0);
    REQUIRE(Statistics::totalMoney(bank)     == 300.0);
    REQUIRE(Statistics::averageBalance(bank) == 150.0);
    REQUIRE(Statistics::richestAccount(bank).getId() == 2);
}

TEST_CASE("Sort by balance ascending") {
    BankSystem bank;
    bank.createAccount(1, MyString("A"), 300.0);
    bank.createAccount(2, MyString("B"), 100.0);
    bank.createAccount(3, MyString("C"), 200.0);
    bank.sortByBalance();
    REQUIRE(bank.getAccounts()[0].getBalance() == 100.0);
    REQUIRE(bank.getAccounts()[1].getBalance() == 200.0);
    REQUIRE(bank.getAccounts()[2].getBalance() == 300.0);
}

TEST_CASE("Sort by id ascending") {
    BankSystem bank;
    bank.createAccount(7, MyString("A"), 1.0);
    bank.createAccount(3, MyString("B"), 1.0);
    bank.createAccount(5, MyString("C"), 1.0);
    bank.sortById();
    REQUIRE(bank.getAccounts()[0].getId() == 3);
    REQUIRE(bank.getAccounts()[1].getId() == 5);
    REQUIRE(bank.getAccounts()[2].getId() == 7);
}
