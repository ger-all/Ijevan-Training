#pragma once

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual bool check() = 0;
    virtual void execute() = 0;
};

