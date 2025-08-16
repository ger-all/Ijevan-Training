#include <iostream>
#include "Button.hpp"
using namespace std;

Button::Button(int id, int parentId, int row, int col, const string& text)
    : Widget(id, parentId, row, col), text(text) {}

void Button::Draw() {
    cout << "  Button ID=" << id
        << " at (" << row << "," << col << ") -> [" << text << "]\n";
}

