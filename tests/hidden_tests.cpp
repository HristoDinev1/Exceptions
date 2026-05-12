// Hidden tests — used by the instructor for grading.
//
// These tests should INITIALLY FAIL (or crash) because the starter code does
// not validate input and does not throw any exceptions. They should PASS only
// after students add validation and throw appropriate standard exceptions.

#include <catch2/catch_test_macros.hpp>

#include "BankSystem.h"
#include "Account.h"
#include "MyVector.h"
#include "MyString.h"
#include "Statistics.h"
#include "FileManager.h"

#include <fstream>
#include <stdexcept>
#include <cstdio>

// ------------------------------------------------------------------
//  MyVector / MyString safety
// ------------------------------------------------------------------

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

// ------------------------------------------------------------------
//  Account / BankSystem validation
// ------------------------------------------------------------------

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

// ------------------------------------------------------------------
//  Statistics on empty bank
// ------------------------------------------------------------------

TEST_CASE("Average balance on empty bank throws std::logic_error") {
    BankSystem bank;
    REQUIRE_THROWS_AS(Statistics::averageBalance(bank), std::logic_error);
}

TEST_CASE("Richest account on empty bank throws std::logic_error") {
    BankSystem bank;
    REQUIRE_THROWS_AS(Statistics::richestAccount(bank), std::logic_error);
}

// ------------------------------------------------------------------
//  FileManager
// ------------------------------------------------------------------

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
