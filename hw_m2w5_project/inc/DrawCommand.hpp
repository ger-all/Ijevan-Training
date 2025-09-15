#pragma once
#include "ICommand.hpp"

class DrawCommand : public ICommand {
public:
    DrawCommand() = default;
    bool check() override;
    void execute() override;
};

