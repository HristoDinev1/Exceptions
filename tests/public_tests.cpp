#include <catch2/catch_test_macros.hpp>

#include "BankSystem.h"
#include "Account.h"
#include "MyVector.h"
#include "MyString.h"
#include "Statistics.h"
#include "Transaction.h"
#include "FileManager.h"

#include <fstream>
#include <stdexcept>
#include <cstdio>

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
    REQUIRE(s == MyString("Hello"));
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

TEST_CASE("MyVector::at on out-of-range index throws std::out_of_range") {
    MyVector<int> v;
    v.push_back(10);
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
}

TEST_CASE("MyVector::pop_back on empty vector throws std::underflow_error") {
    MyVector<int> v;
    REQUIRE_THROWS_AS(v.pop_back(), std::underflow_error);
}

TEST_CASE("MyVector::reserve with absurd size throws std::length_error") {
    MyVector<int> v;
    REQUIRE_THROWS_AS(v.reserve(static_cast<std::size_t>(-1)), std::length_error);
}

TEST_CASE("MyString out-of-range access throws std::out_of_range") {
    MyString s("Hi");
    REQUIRE_THROWS_AS(s[10], std::out_of_range);
}

TEST_CASE("Negative deposit throws std::invalid_argument") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE_THROWS_AS(bank.deposit(1, -10.0), std::invalid_argument);
}

TEST_CASE("Negative withdraw throws std::invalid_argument") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE_THROWS_AS(bank.withdraw(1, -10.0), std::invalid_argument);
}

TEST_CASE("Withdraw more than balance throws std::underflow_error") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 50.0);
    REQUIRE_THROWS_AS(bank.withdraw(1, 100.0), std::underflow_error);
}

TEST_CASE("Duplicate account ID throws std::invalid_argument") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE_THROWS_AS(
        bank.createAccount(1, MyString("Bob"), 50.0),
        std::invalid_argument);
}

TEST_CASE("Finding a non-existing account throws std::out_of_range") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE_THROWS_AS(bank.findAccount(99), std::out_of_range);
}

TEST_CASE("Transfer to non-existing account throws std::out_of_range") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE_THROWS_AS(bank.transfer(1, 99, 10.0), std::out_of_range);
}

TEST_CASE("Transfer to the same account throws std::logic_error") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    REQUIRE_THROWS_AS(bank.transfer(1, 1, 10.0), std::logic_error);
}

TEST_CASE("Negative transfer amount throws std::invalid_argument") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 100.0);
    bank.createAccount(2, MyString("Bob"),   50.0);
    REQUIRE_THROWS_AS(bank.transfer(1, 2, -10.0), std::invalid_argument);
}

TEST_CASE("Negative initial balance throws std::invalid_argument") {
    BankSystem bank;
    REQUIRE_THROWS_AS(
        bank.createAccount(1, MyString("X"), -50.0),
        std::invalid_argument);
}

TEST_CASE("Non-positive account ID throws std::invalid_argument") {
    BankSystem bank;
    REQUIRE_THROWS_AS(
        bank.createAccount(-5, MyString("Alice"), 100.0),
        std::invalid_argument);
}

TEST_CASE("Empty owner name throws std::invalid_argument") {
    BankSystem bank;
    REQUIRE_THROWS_AS(
        bank.createAccount(1, MyString(""), 100.0),
        std::invalid_argument);
}

TEST_CASE("Deposit causing overflow throws std::overflow_error") {
    BankSystem bank;
    bank.createAccount(1, MyString("Alice"), 1e308);
    REQUIRE_THROWS_AS(bank.deposit(1, 1e308), std::overflow_error);
}

TEST_CASE("Average balance on empty bank throws std::logic_error") {
    BankSystem bank;
    REQUIRE_THROWS_AS(Statistics::averageBalance(bank), std::logic_error);
}

TEST_CASE("Richest account on empty bank throws std::logic_error") {
    BankSystem bank;
    REQUIRE_THROWS_AS(Statistics::richestAccount(bank), std::logic_error);
}

TEST_CASE("Loading a non-existing file throws std::runtime_error") {
    BankSystem bank;
    REQUIRE_THROWS_AS(
        FileManager::load(bank, MyString("does_not_exist_xyz_123.txt")),
        std::runtime_error);
}

TEST_CASE("Loading a malformed file throws std::runtime_error") {
    const char* fname = "malformed_test_file.txt";
    {
        std::ofstream out(fname);
        out << "not a number\nrandom garbage on the next line\n";
    }
    BankSystem bank;
    REQUIRE_THROWS_AS(
        FileManager::load(bank, MyString(fname)),
        std::runtime_error);
    std::remove(fname);
}
