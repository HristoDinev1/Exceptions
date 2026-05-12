#include "FileManager.h"

#include <fstream>
#include <string>

void FileManager::save(const BankSystem& bank, const MyString& filename) {
    std::ofstream out(filename.c_str());
    const MyVector<Account>& accounts = bank.getAccounts();
    out << accounts.size() << '\n';
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        const Account& acc = accounts[i];
        out << acc.getId()        << '\n'
            << acc.getOwnerName() << '\n'
            << acc.getBalance()   << '\n';
    }
}

void FileManager::load(BankSystem& bank, const MyString& filename) {
    std::ifstream in(filename.c_str());
    std::size_t count = 0;
    in >> count;
    for (std::size_t i = 0; i < count; ++i) {
        int         id      = 0;
        std::string owner;
        double      balance = 0.0;
        in >> id >> owner >> balance;
        bank.createAccount(id, MyString(owner.c_str()), balance);
    }
}
