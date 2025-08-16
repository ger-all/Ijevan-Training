#include "Widget.hpp"

// Constructor
Widget::Widget(int id, int parentId, int row, int col)
    : id(id), parentId(parentId), row(row), col(col) {}

// Destructor
Widget::~Widget() {}

// Getters
int Widget::GetId() const { return id; }
int Widget::GetParentId() const { return parentId; }
int Widget::GetRow() const { return row; }
int Widget::GetCol() const { return col; }

