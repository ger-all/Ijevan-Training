#include "Table.hpp"
#include <iostream>
using namespace std;

Table::Table(int id, int parentId, int row, int col, int rowCount, int colCount)
    : Widget(id, parentId, row, col), rowCount(rowCount), colCount(colCount) {}

void Table::Draw() {
    cout << "  Table ID=" << id
        << " size=" << rowCount << "x" << colCount
        << " at (" << row << "," << col << ")\n";
}

