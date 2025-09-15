#include "AddTextCommand.hpp"
#include "WidgetManager.hpp"
#include <iostream>

AddTextCommand::AddTextCommand(const std::vector<std::string>& args_) : args(args_) {}

bool AddTextCommand::check() {
    if (args.size() < 6) {
        std::cout << "Usage: add_text <id> <text> <parentId> <row> <col>\n";
        return false;
    }
    try {
        id = std::stoi(args[1]);
        text = args[2];
        parentId = std::stoi(args[3]);
        row = std::stoi(args[4]);
        col = std::stoi(args[5]);
    } catch (...) {
        std::cout << "Error: invalid arguments for add_text.\n";
        return false;
    }
    WidgetManager& wm = WidgetManager::getInstance();
    if (!wm.isAvailableId(id)) return false;
    if (!wm.isAvailableParentId(parentId)) return false;
    return true;
}

void AddTextCommand::execute() {
    WidgetManager::getInstance().add_text(id, text, parentId, row, col);
}

