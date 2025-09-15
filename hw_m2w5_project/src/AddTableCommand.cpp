#include "AddTableCommand.hpp"
#include "WidgetManager.hpp"
#include <iostream>

AddTableCommand::AddTableCommand(const std::vector<std::string>& args_) : args(args_) {}

bool AddTableCommand::check() {
    if (args.size() < 7) {
        std::cout << "Usage: add_table <id> <rows> <cols> <parentId> <row> <col>\n";
        return false;
    }
    try {
        id = std::stoi(args[1]);
        rows = std::stoi(args[2]);
        cols = std::stoi(args[3]);
        parentId = std::stoi(args[4]);
        row = std::stoi(args[5]);
        col = std::stoi(args[6]);
    } catch (...) {
        std::cout << "Error: invalid arguments for add_table.\n";
        return false;
    }
    WidgetManager& wm = WidgetManager::getInstance();
    if (!wm.isAvailableId(id)) return false;
    if (!wm.isAvailableParentId(parentId)) return false;
    return true;
}

void AddTableCommand::execute() {
    WidgetManager::getInstance().add_table(id, rows, cols, parentId, row, col);
}

