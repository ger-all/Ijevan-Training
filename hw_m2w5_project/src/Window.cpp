#include <iostream>
#include "Window.hpp"
using namespace std;

Window::Window(int id, int parentId, int row, int col, int rowCount, int colCount)
    : Widget(id, parentId, row, col), rowCount(rowCount), colCount(colCount) {}

bool Window::AddChild(Widget* child) {
    int cRow = child->GetRow();
    int cCol = child->GetCol();

    if (cRow < 0 || cCol < 0 || cRow >= rowCount || cCol >= colCount) {
        cout << "Error: child widget does not fit inside parent window\n";
        return false;
    }

    for (Widget* w : children) {
        if (w->GetRow() == cRow && w->GetCol() == cCol) {
            cout << "Error: another widget already exists at (" << cRow << "," << cCol << ")\n";
            return false;
        }
    }

    children.push_back(child);
    return true;
}

void Window::Draw() {
    cout << "Window ID=" << id
        << " size=" << rowCount << "x" << colCount
        << " at (" << row << "," << col << ")\n";

    for (Widget* c : children) {
        c->Draw();
    }
}

