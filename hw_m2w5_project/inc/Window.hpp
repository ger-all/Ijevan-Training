#pragma once
#include "Widget.hpp"
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Window : public Widget {
    int rowCount, colCount;
    vector<Widget*> children; // only non-owning, ownership in global map

public:
    Window(int id, int parentId, int row, int col, int rowCount, int colCount);

    bool AddChild(Widget* child);
    void Draw() override;
};

