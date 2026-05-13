#include "FileManager.h"

#include <fstream>
#include <stdexcept>
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
    if (!in)
        throw std::runtime_error("FileManager::load: cannot open file");
    std::size_t count = 0;
    if (!(in >> count))
        throw std::runtime_error("FileManager::load: malformed file");
    for (std::size_t i = 0; i < count; ++i) {
        int         id      = 0;
        std::string owner;
        double      balance = 0.0;
        if (!(in >> id >> owner >> balance))
            throw std::runtime_error("FileManager::load: malformed file");
        bank.createAccount(id, MyString(owner.c_str()), balance);
    }
}
