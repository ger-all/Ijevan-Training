#pragma once
#include "Widget.hpp"
using namespace std;

class Table : public Widget {
    int rowCount, colCount;

public:
    Table(int id, int parentId, int row, int col, int rowCount, int colCount);
    void Draw() override;
};

