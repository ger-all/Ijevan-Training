#include <iostream>
#include <sstream>
#include <vector>

#include "WidgetManager.hpp"
#include "Widget.hpp"
#include "Window.hpp"
#include "Text.hpp"
#include "Table.hpp"
#include "Button.hpp"
#include "ICommand.hpp"
#include "AddWindowCommand.hpp"
#include "AddTextCommand.hpp"
#include "AddButtonCommand.hpp"
#include "AddTableCommand.hpp"
#include "DrawCommand.hpp"
#include "HelpCommand.hpp"

using namespace std;

// === Constructor / Destructor ===
WidgetManager::WidgetManager() {}
WidgetManager::~WidgetManager() {
    for (auto& kv : widgets) {
        delete kv.second;
    }
}

// === Singleton getter ===
WidgetManager& WidgetManager::getInstance() {
    static WidgetManager instance;
    return instance;
}

// === Run loop ===
void WidgetManager::run() {
    static bool bIsRunning = false;
    if (bIsRunning) return;
    bIsRunning = true;

    printCommands();
    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line == "exit") break;
        processCommand(line);
    }
}

// === Command processing ===
void WidgetManager::processCommand(const string& line) {
    vector<string> args = tokenize(line);
    if (args.empty()) return;

    ICommand* pCmd = parseCommand(args);

    if (pCmd) {
        if (pCmd->check()) {
            pCmd->execute();
        }
        delete pCmd;
    }
}

// === Tokenize function ===
vector<string> WidgetManager::tokenize(const string& line) {
    vector<string> tokens;
    istringstream ss(line);
    string word;
    while (ss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

// === Parse command into ICommand instance ===
ICommand* WidgetManager::parseCommand(const vector<string>& args) {
    if (args[0] == "add_window") return new AddWindowCommand(args);
    if (args[0] == "add_text") return new AddTextCommand(args);
    if (args[0] == "add_button") return new AddButtonCommand(args);
    if (args[0] == "add_table") return new AddTableCommand(args);
    if (args[0] == "draw") return new DrawCommand();
    if (args[0] == "help") return new HelpCommand();
    if (args[0] == "exit") exit(0);

    cout << "Unknown command: " << args[0] << "\n";
    return nullptr;
}

// === Add functions ===
bool WidgetManager::add_to_parent_if_possible(Widget* w, int parentId) {
    if (parentId == -1) return true;

    Window* parent = dynamic_cast<Window*>(widgets[parentId]);
    if (!parent) {
        cout << "Error: parent must be a Window\n";
        return false;
    }

    if (!(parent->AddChild(w))) {
        return false;
    }
    return true;
}

void WidgetManager::add_window(int id, int rows, int cols, int parentId, int row, int col) {
    Window* w = new Window(id, parentId, row, col, rows, cols);

    if (!add_to_parent_if_possible(w, parentId)) {
        delete w;
        return;
    }

    widgets[id] = w;
}

void WidgetManager::add_text(int id, const string& text, int parentId, int row, int col) {
    Text* t = new Text(id, parentId, row, col, text);

    if (!add_to_parent_if_possible(t, parentId)) {
        delete t;
        return;
    }

    widgets[id] = t;
}

void WidgetManager::add_table(int id, int rows, int cols, int parentId, int row, int col) {
    Table* tb = new Table(id, parentId, row, col, rows, cols);

    if (!add_to_parent_if_possible(tb, parentId)) {
        delete tb;
        return;
    }

    widgets[id] = tb;
}

void WidgetManager::add_button(int id, const string& text, int parentId, int row, int col) {
    Button* b = new Button(id, parentId, row, col, text);

    if (!add_to_parent_if_possible(b, parentId)) {
        delete b;
        return;
    }

    widgets[id] = b;
}

// === Draw all root windows ===
void WidgetManager::draw_all() const {
    for (auto& kv : widgets) {
        if (kv.second->GetParentId() == -1) {
            kv.second->Draw();
        }
    }
}

// === Print commands ===
void WidgetManager::printCommands() const {
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

// === Check functions for Command classes ===
bool WidgetManager::isAvailableId(int id) const {
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

bool WidgetManager::isAvailableParentId(int parentId) const {
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

bool WidgetManager::isAvailableParentId_window(int parentId) const {
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

