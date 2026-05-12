#pragma once
#include "BankSystem.h"

namespace banking
{
    class Menu
    {
    private:
        BankSystem& bank;

    public:
        Menu(BankSystem& bank);
        void run();
    };
}
