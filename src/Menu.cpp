#include "Menu.h"
#include "Statistics.h"
#include "FileManager.h"

#include <iostream>
#include <string>

Menu::Menu(BankSystem& bank) : bank(bank) {}

void Menu::showMainMenu() {
    std::cout << "\n=== Banking System ===\n"
              << "1. Create account\n"
              << "2. Deposit\n"
              << "3. Withdraw\n"
              << "4. Transfer\n"
              << "5. Find account\n"
              << "6. Print all accounts\n"
              << "7. Sort accounts\n"
              << "8. Show statistics\n"
              << "9. Save / Load\n"
              << "0. Exit\n"
              << "Choice: ";
}

void Menu::handleCreateAccount() {
    int id;
    std::string name;
    double initial;
    std::cout << "Account ID: ";       std::cin >> id;
    std::cout << "Owner name: ";       std::cin >> name;
    std::cout << "Initial balance: ";  std::cin >> initial;
    bank.createAccount(id, MyString(name.c_str()), initial);
    std::cout << "Account created.\n";
}

void Menu::handleDeposit() {
    int id; double amount;
    std::cout << "Account ID: "; std::cin >> id;
    std::cout << "Amount: ";     std::cin >> amount;
    bank.deposit(id, amount);
    std::cout << "Deposited.\n";
}

void Menu::handleWithdraw() {
    int id; double amount;
    std::cout << "Account ID: "; std::cin >> id;
    std::cout << "Amount: ";     std::cin >> amount;
    bank.withdraw(id, amount);
    std::cout << "Withdrawn.\n";
}

void Menu::handleTransfer() {
    int fromId, toId; double amount;
    std::cout << "From account: "; std::cin >> fromId;
    std::cout << "To account: ";   std::cin >> toId;
    std::cout << "Amount: ";       std::cin >> amount;
    bank.transfer(fromId, toId, amount);
    std::cout << "Transferred.\n";
}

void Menu::handleFindAccount() {
    int id;
    std::cout << "Account ID: "; std::cin >> id;
    const Account& acc = bank.findAccount(id);
    acc.printSummary();
    acc.printHistory();
}

void Menu::handlePrintAll() {
    bank.printAllAccounts();
}

void Menu::handleSort() {
    int choice;
    std::cout << "Sort by  1) ID   2) Balance: ";
    std::cin >> choice;
    if (choice == 1) bank.sortById();
    else             bank.sortByBalance();
    std::cout << "Sorted.\n";
}

void Menu::handleStatistics() {
    Statistics::printStatistics(bank);
}

void Menu::handleSaveLoad() {
    int choice;
    std::cout << "1) Save   2) Load: ";
    std::cin >> choice;
    std::string filename;
    std::cout << "Filename: ";
    std::cin >> filename;
    if (choice == 1) {
        FileManager::save(bank, MyString(filename.c_str()));
        std::cout << "Saved.\n";
    } else {
        FileManager::load(bank, MyString(filename.c_str()));
        std::cout << "Loaded.\n";
    }
}

void Menu::run() {
    int choice = -1;
    while (choice != 0) {
        showMainMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: handleCreateAccount(); break;
            case 2: handleDeposit();       break;
            case 3: handleWithdraw();      break;
            case 4: handleTransfer();      break;
            case 5: handleFindAccount();   break;
            case 6: handlePrintAll();      break;
            case 7: handleSort();          break;
            case 8: handleStatistics();    break;
            case 9: handleSaveLoad();      break;
            case 0: std::cout << "Bye!\n"; break;
        }
    }
}
