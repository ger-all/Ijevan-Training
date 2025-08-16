#pragma once
#include "Widget.hpp"
#include <string>
using namespace std;

class Button : public Widget {
    string text;

public:
    Button(int id, int parentId, int row, int col, const string& text);
    void Draw() override;
};

