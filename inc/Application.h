#pragma once
#include "Menu.h"

namespace banking
{
    class Application
    {
    private:
        static Application* instance;

        BankSystem bank;
        Menu menu;

        Application();

    public:
        static Application& getInstance();
        void run();
    };
}
