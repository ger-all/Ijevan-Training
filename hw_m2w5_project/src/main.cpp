#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "Widget.hpp"
#include "Window.hpp"
#include "Text.hpp"
#include "Table.hpp"
#include "Button.hpp"
using namespace std;

// === Global storage ===
map<int, Widget*> widgets;

// === Check functions ===
bool isAvailableId(int id) {
    if (id < 0) {
        cout << "Error: 'id' must be positive number" << endl;
        return false;
    }

    if (widgets.find(id) != widgets.end()) {
        cout << "Error: widget with id " << id << " already exists!" << endl;
        return false;
    }

    return true;
}

bool isAvailableParentId(int parentId) {
    if (parentId < 0) {
        cout << "Error: 'parentId' must be positive number" << endl;
        return false;
    }

    auto parentIt = widgets.find(parentId);
    if (parentIt == widgets.end()) {
        cout << "Error: Parent window with id " << parentId << " not found!" << endl;
        return false;
    }

    return true;
}

bool isAvailableParentId_window(int parentId) {
    if (parentId != -1) {
        if (parentId < 0) {
            cout << "Error: 'parentId' must be positive number or -1" << endl;
            return false;
        }

        auto parentIt = widgets.find(parentId);
        if (parentIt == widgets.end()) {
            cout << "Error: Parent window with id " << parentId << " not found!" << endl;
            return false;
        }
    }
    return true;
}

bool add_to_parent_if_possible(Widget* w, int parentId) {
    if (parentId == -1) return true; // root window

    Window* parent = dynamic_cast<Window*>(widgets[parentId]);
    if (!parent) {
        cout << "Error: parent must be a Window\n";
        return false;
    }

    if (!(parent->AddChild(w))) {
        return false; // նույն տեղում արդեն կա
    }

    return true;
}

// === Add functions ===
void add_window(int id, int rows, int cols, int parentId = -1, int row = -1, int col = -1) {
    if (!isAvailableId(id)) return;
    if (!isAvailableParentId_window(parentId)) return;

    Window* w = new Window(id, parentId, row, col, rows, cols);

    if (!add_to_parent_if_possible(w, parentId)) {
        delete w;
        return;
    }

    widgets[id] = w;
}

void add_text(int id, const string& text, int parentId, int row, int col) {
    if (!isAvailableId(id)) return;
    if (!isAvailableParentId(parentId)) return;

    Text* t = new Text(id, parentId, row, col, text);

    if (!add_to_parent_if_possible(t, parentId)) {
        delete t;
        return;
    }

    widgets[id] = t;
}

void add_table(int id, int rows, int cols, int parentId, int row, int col) {
    if (!isAvailableId(id)) return;
    if (!isAvailableParentId(parentId)) return;
    
    Table* tb = new Table(id, parentId, row, col, rows, cols);

    if (!add_to_parent_if_possible(tb, parentId)) {
        delete tb;
        return;
    }

    widgets[id] = tb;
}

void add_button(int id, const string& text, int parentId, int row, int col) {
    if (!isAvailableId(id)) return;
    if (!isAvailableParentId(parentId)) return;

    Button* b = new Button(id, parentId, row, col, text);

    if (!add_to_parent_if_possible(b, parentId)) {
        delete b;
        return;
    }

    widgets[id] = b;
}

// === Draw all root windows ===
void draw_all() {
    for (auto& kv : widgets) {
        if (kv.second->GetParentId() == -1) {
            kv.second->Draw();
        }
    }
}

// === Print all commands ===
void printCommands() {
    cout << "CLI Window Manager\n";
    cout << "Enter commands, type 'exit' to quit.\n\n";
    cout << "Available commands:\n";
    cout << "  add_window <id> <rowCount> <colCount> [parentWindowId=-1] [row=-1] [col=-1]\n";
    cout << "  add_text <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  add_table <id> <rowCount> <colCount> <parentWindowId> <row> <col>\n";
    cout << "  add_button <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  draw\n";
    cout << "  help\n";
    cout << "  exit\n\n";
}

// === Main loop ===
int main() {
    string line;

    printCommands();

    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "exit") break;

        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "add_window") {
            int id, rCount, cCount, pId = -1, row = -1, col = -1;
            ss >> id >> rCount >> cCount >> pId >> row >> col;
            add_window(id, rCount, cCount, pId, row, col);
        }
        else if (cmd == "add_text") {
            int id, pId, row, col;
            string text;
            ss >> id;
            ss.ignore(); // skip space
            getline(ss, text, '"'); // first quote
            getline(ss, text, '"'); // actual text
            ss >> pId >> row >> col;
            add_text(id, text, pId, row, col);
        }
        else if (cmd == "add_table") {
            int id, rCount, cCount, pId, row, col;
            ss >> id >> rCount >> cCount >> pId >> row >> col;
            add_table(id, rCount, cCount, pId, row, col);
        }
        else if (cmd == "add_button") {
            int id, pId, row, col;
            string text;
            ss >> id;
            ss.ignore();
            getline(ss, text, '"');
            getline(ss, text, '"');
            ss >> pId >> row >> col;
            add_button(id, text, pId, row, col);
        }
        else if (cmd == "draw") {
            draw_all();
        }
        else if (cmd == "help") {
            printCommands();
        }
        else {
            cout << "Unknown command: " << cmd << "\n";
        }
    }

    // Clean up
    for (auto& kv : widgets) {
        delete kv.second;
    }

    return 0;
}

