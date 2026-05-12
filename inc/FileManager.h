#pragma once
#include "BankSystem.h"
#include "MyString.h"

class FileManager {
public:
    static void save(const BankSystem& bank, const MyString& filename);
    static void load(BankSystem& bank,       const MyString& filename);
};
