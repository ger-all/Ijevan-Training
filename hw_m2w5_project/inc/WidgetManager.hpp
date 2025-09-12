#pragma once

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

class WidgetManager {
    // The singleton starts CLI immediately and program ends when user exits.

private:
    // === Storage ===
    map<int, Widget*> widgets;

    WidgetManager();
    ~WidgetManager();

    // === Helper function ===
    void processCommand(const string& line);

    // === Check functions ===
    bool isAvailableId(int id) const;
    bool isAvailableParentId(int parentId) const;
    bool isAvailableParentId_window(int parentId) const;
    bool add_to_parent_if_possible(Widget* w, int parentId);

    // === Add functions ===
    void add_window(int id, int rows, int cols, int parentId = -1, int row = -1, int col = -1);
    void add_text(int id, const string& text, int parentId, int row, int col);
    void add_table(int id, int rows, int cols, int parentId, int row, int col);
    void add_button(int id, const string& text, int parentId, int row, int col);

    // === Draw all root windows ===
    void draw_all() const;

    // === Print all commands ===
    void printCommands() const;

public:
    // === Don't allow to do copy or use assignment operator ===
    WidgetManager(const WidgetManager&) = delete;
    WidgetManager& operator=(const WidgetManager&) = delete;

    // === Return instance (Singleton) ===
    static WidgetManager& getInstance();
};

