#include "Application.h"

namespace banking
{
    Application* Application::instance = nullptr;

    Application::Application()
        : menu(bank)
    {
    }

    Application& Application::getInstance()
    {
        if (!instance)
        {
            instance = new Application();
        }

        return *instance;
    }

    void Application::run()
    {
        menu.run();
    }
}
