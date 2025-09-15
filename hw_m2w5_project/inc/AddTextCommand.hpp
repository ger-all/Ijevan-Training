#pragma once
#include "ICommand.hpp"
#include <vector>
#include <string>

class AddTextCommand : public ICommand {
private:
    std::vector<std::string> args;
    int id, parentId, row, col;
    std::string text;

public:
    AddTextCommand(const std::vector<std::string>& args_);
    bool check() override;
    void execute() override;
};

