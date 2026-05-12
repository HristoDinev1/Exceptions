#include "Application.h"

Application::Application()
    : bank(), menu(bank) {}

Application& Application::getInstance() {
    static Application instance;
    return instance;
}

void Application::run() {
    // Currently no try/catch on purpose — this is where students will add the
    // central exception-handling boundary later.
    menu.run();
}
