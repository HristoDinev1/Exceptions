#pragma once
#include "BankSystem.h"
#include "Menu.h"

class Application {
private:
    BankSystem bank;
    Menu       menu;

    Application();

public:
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;

    static Application& getInstance();
    void run();
};
