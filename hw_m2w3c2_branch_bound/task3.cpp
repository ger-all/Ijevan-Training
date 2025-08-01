#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 4;

bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < SIZE; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check 2x2 subgrid
    int startRow = (row / 2) * 2;
    int startCol = (col / 2) * 2;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= SIZE; ++num) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row][col] = 0; // backtrack
                    }
                }
                return false; // no number fits
            }
        }
    }
    return true; // all cells are filled
}

void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> board = {
        {1, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 3}
    };

    if (solveSudoku(board)) {
        cout << "Filled Sudoku:" << endl;
        printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}

