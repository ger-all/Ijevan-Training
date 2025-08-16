#include "Text.hpp"
#include <iostream>
using namespace std;

Text::Text(int id, int parentId, int row, int col, const string& text)
    : Widget(id, parentId, row, col), text(text) {}

void Text::Draw() {
    cout << "  Text ID=" << id
        << " at (" << row << "," << col << ") -> \"" << text << "\"\n";
}

