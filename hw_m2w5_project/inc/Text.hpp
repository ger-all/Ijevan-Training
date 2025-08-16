#pragma once
#include "Widget.hpp"
#include <string>
using namespace std;

class Text : public Widget {
    string text;

public:
    Text(int id, int parentId, int row, int col, const string& text);
    void Draw() override;
};

