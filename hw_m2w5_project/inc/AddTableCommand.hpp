#pragma once
#include "ICommand.hpp"
#include <vector>
#include <string>

class AddTableCommand : public ICommand {
private:
    std::vector<std::string> args;
    int id, rows, cols, parentId, row, col;

public:
    AddTableCommand(const std::vector<std::string>& args_);
    bool check() override;
    void execute() override;
};

