#pragma once
#include "BankSystem.h"

class Menu {
private:
    BankSystem& bank;

    void showMainMenu();
    void handleCreateAccount();
    void handleDeposit();
    void handleWithdraw();
    void handleTransfer();
    void handleFindAccount();
    void handlePrintAll();
    void handleSort();
    void handleStatistics();
    void handleSaveLoad();

public:
    Menu(BankSystem& bank);

    void run();
};
