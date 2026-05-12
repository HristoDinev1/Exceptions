#pragma once
#include "BankSystem.h"
#include "Menu.h"

// Singleton — central application coordinator.
// This is the place where students will add the central try/catch later.
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
