#pragma once
#include <iostream>
using namespace std;

// === Base Widget Class ===
class Widget {
protected:
    int id;
    int parentId;
    int row, col;

public:
    Widget(int id, int parentId, int row, int col);
    virtual void Draw() = 0; // Pure virtual
    virtual ~Widget();

    int GetId() const;
    int GetParentId() const;
    int GetRow() const;
    int GetCol() const;
};

