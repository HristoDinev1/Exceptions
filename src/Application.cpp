#include "Application.h"

Application::Application()
    : bank(), menu(bank) {}

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

void Application::run() {
    menu.run();
}
