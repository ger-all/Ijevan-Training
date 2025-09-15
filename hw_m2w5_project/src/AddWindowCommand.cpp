#include "AddWindowCommand.hpp"
#include "WidgetManager.hpp"
#include <iostream>

AddWindowCommand::AddWindowCommand(const std::vector<std::string>& args_) : args(args_) {}

bool AddWindowCommand::check() {
    if (args.size() < 4) {
        std::cout << "Usage: add_window <id> <rows> <cols> [parentId=-1] [row=-1] [col=-1]\n";
        return false;
    }
    try {
        id = std::stoi(args[1]);
        rows = std::stoi(args[2]);
        cols = std::stoi(args[3]);
        parentId = args.size() > 4 ? std::stoi(args[4]) : -1;
        row = args.size() > 5 ? std::stoi(args[5]) : -1;
        col = args.size() > 6 ? std::stoi(args[6]) : -1;
    } catch (...) {
        std::cout << "Error: invalid arguments for add_window.\n";
        return false;
    }
    WidgetManager& wm = WidgetManager::getInstance();
    if (!wm.isAvailableId(id)) return false;
    if (!wm.isAvailableParentId_window(parentId)) return false;
    return true;
}

void AddWindowCommand::execute() {
    WidgetManager::getInstance().add_window(id, rows, cols, parentId, row, col);
}

