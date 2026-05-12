#include "Menu.h"
#include <iostream>

namespace banking
{
    Menu::Menu(BankSystem& bank)
        : bank(bank)
    {
    }

    void Menu::run()
    {
        int choice = -1;

        while (choice != 0)
        {
            std::cout << "1.Create\n2.Deposit\n3.Withdraw\n4.Print\n0.Exit\n";
            std::cin >> choice;

            if (choice == 1)
            {
                int id;
                std::string name;
                double balance;

                std::cin >> id >> name >> balance;
                bank.createAccount(id, name, balance);
            }
            else if (choice == 2)
            {
                int id;
                double amount;

                std::cin >> id >> amount;
                bank.deposit(id, amount);
            }
            else if (choice == 3)
            {
                int id;
                double amount;

                std::cin >> id >> amount;
                bank.withdraw(id, amount);
            }
            else if (choice == 4)
            {
                bank.printAccounts();
            }
        }
    }
}
