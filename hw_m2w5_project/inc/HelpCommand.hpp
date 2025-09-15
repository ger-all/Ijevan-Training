#pragma once
#include "ICommand.hpp"

class HelpCommand : public ICommand {
public:
    HelpCommand() = default;
    bool check() override;
    void execute() override;
};

