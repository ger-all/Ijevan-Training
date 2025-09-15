#include "HelpCommand.hpp"
#include "WidgetManager.hpp"

bool HelpCommand::check() {
    return true;
}

void HelpCommand::execute() {
    WidgetManager::getInstance().printCommands();
}

