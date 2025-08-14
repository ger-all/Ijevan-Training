#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <memory>

using namespace std;

// === Base Widget Class ===
class Widget {
protected:
    int id;
    int parentId;
    int row, col;

public:
    Widget(int id, int parentId, int row, int col)
        : id(id), parentId(parentId), row(row), col(col) {}

    virtual void Draw() = 0; // Pure virtual
    virtual ~Widget() {}

    int GetId() const { return id; }
    int GetParentId() const { return parentId; }
};

// === Window Class ===
class Window : public Widget {
    int rowCount, colCount;
    vector<Widget*> children;

public:
    Window(int id, int parentId, int row, int col, int rowCount, int colCount)
        : Widget(id, parentId, row, col), rowCount(rowCount), colCount(colCount) {}

    void AddChild(Widget* child) {
        // stugel chapery
        children.push_back(child);
    }

    void Draw() override {
        cout << "Window ID=" << id
            << " size=" << rowCount << "x" << colCount
            << " at (" << row << "," << col << ")\n";

        for (auto c : children) {
            c->Draw();
        }
    }
};

//stugel 3 obyektnery chaperov, nor sarqel

// === Text Class ===
class Text : public Widget {
    string text;

public:
    Text(int id, int parentId, int row, int col, const string& text)
        : Widget(id, parentId, row, col), text(text) {}

    void Draw() override {
        cout << "  Text ID=" << id
            << " at (" << row << "," << col << ") -> \"" << text << "\"\n";
    }
};

// === Table Class ===
class Table : public Widget {
    int rowCount, colCount;

public:
    Table(int id, int parentId, int row, int col, int rowCount, int colCount)
        : Widget(id, parentId, row, col), rowCount(rowCount), colCount(colCount) {}

    void Draw() override {
        cout << "  Table ID=" << id
            << " size=" << rowCount << "x" << colCount
            << " at (" << row << "," << col << ")\n";
    }
};

// === Button Class ===
class Button : public Widget {
    string text;

public:
    Button(int id, int parentId, int row, int col, const string& text)
        : Widget(id, parentId, row, col), text(text) {}

    void Draw() override {
        cout << "  Button ID=" << id
            << " at (" << row << "," << col << ") -> [" << text << "]\n";
    }
};

// === Global storage ===
map<int, Widget*> widgets;

// === Add functions ===
void add_window(int id, int rows, int cols, int parentId = -1, int row = -1, int col = -1) {
    Window* w = new Window(id, parentId, row, col, rows, cols);
    widgets[id] = w; //եթե չկար նման key նորն է ստեղծվում, եթե կար համապատասխան value-ն է փոխվում
    if (parentId != -1) {
        auto parent = dynamic_cast<Window*>(widgets[parentId]);
        if (parent) parent->AddChild(w);
        // delete kam skzbic ara sax stugumnery
    }
}

void add_text(int id, const string& text, int parentId, int row, int col) {
    Text* t = new Text(id, parentId, row, col, text);
    widgets[id] = t;
    auto parent = dynamic_cast<Window*>(widgets[parentId]);
    if (parent) parent->AddChild(t);
}

void add_table(int id, int rows, int cols, int parentId, int row, int col) {
    Table* tb = new Table(id, parentId, row, col, rows, cols);
    widgets[id] = tb;
    auto parent = dynamic_cast<Window*>(widgets[parentId]);
    if (parent) parent->AddChild(tb);
}

void add_button(int id, const string& text, int parentId, int row, int col) {
    Button* b = new Button(id, parentId, row, col, text);
    widgets[id] = b;
    auto parent = dynamic_cast<Window*>(widgets[parentId]);
    if (parent) parent->AddChild(b);
}

// === Draw all root windows ===
void draw_all() {
    for (auto& kv : widgets) {
        if (kv.second->GetParentId() == -1) {
            kv.second->Draw();
        }
    }
}

void printCommands() {
    cout << "CLI Window Manager\n";
    cout << "Enter commands, type 'exit' to quit.\n\n";
    cout << "Available commands:\n";
    cout << "  add_window <id> <rowCount> <colCount> [parentWindowId=-1] [row=-1] [col=-1]\n";
    cout << "  add_text <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  add_table <id> <rowCount> <colCount> <parentWindowId> <row> <col>\n";
    cout << "  add_button <id> <text> <parentWindowId> <row> <col>\n";
    cout << "  draw\n";
    cout << "  exit\n\n";
}

// === Main loop ===
int main() {
    string line;

    printCommands();
    // himanvores mapy, inchu es ogtagorcel
    // is(available() function unena
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
            // example: "hello", it will work ok
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

