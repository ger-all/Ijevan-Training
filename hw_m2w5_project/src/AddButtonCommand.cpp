#include "AddButtonCommand.hpp"
#include "WidgetManager.hpp"
#include <iostream>

AddButtonCommand::AddButtonCommand(const std::vector<std::string>& args_) : args(args_) {}

bool AddButtonCommand::check() {
    if (args.size() < 6) {
        std::cout << "Usage: add_button <id> <text> <parentId> <row> <col>\n";
        return false;
    }
    try {
        id = std::stoi(args[1]);
        text = args[2];
        parentId = std::stoi(args[3]);
        row = std::stoi(args[4]);
        col = std::stoi(args[5]);
    } catch (...) {
        std::cout << "Error: invalid arguments for add_button.\n";
        return false;
    }
    WidgetManager& wm = WidgetManager::getInstance();
    if (!wm.isAvailableId(id)) return false;
    if (!wm.isAvailableParentId(parentId)) return false;
    return true;
}

void AddButtonCommand::execute() {
    WidgetManager::getInstance().add_button(id, text, parentId, row, col);
}

