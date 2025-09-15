#pragma once
#include "ICommand.hpp"
#include <vector>
#include <string>

class AddWindowCommand : public ICommand {
private:
    std::vector<std::string> args;
    int id, rows, cols, parentId, row, col;

public:
    AddWindowCommand(const std::vector<std::string>& args_);
    bool check() override;
    void execute() override;
};

