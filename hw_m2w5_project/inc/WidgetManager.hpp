#pragma once
#include <string>
#include <map>
#include <vector>

class Widget;
class ICommand;

class WidgetManager {
private:
    // Singleton instance
    WidgetManager();
    ~WidgetManager();

    // Disable copy and assignment
    WidgetManager(const WidgetManager&) = delete;
    WidgetManager& operator=(const WidgetManager&) = delete;

    // Storage for all widgets
    std::map<int, Widget*> widgets;

    // === Helper functions ===
    bool add_to_parent_if_possible(Widget* w, int parentId);

    ICommand* parseCommand(const std::vector<std::string>& args);
    std::vector<std::string> tokenize(const std::string& line);

public:
    static WidgetManager& getInstance();

    // === Public functions ===
    void run();
    void processCommand(const std::string& line);

    // === Add functions ===
    void add_window(int id, int rows, int cols, int parentId, int row, int col);
    void add_text(int id, const std::string& text, int parentId, int row, int col);
    void add_table(int id, int rows, int cols, int parentId, int row, int col);
    void add_button(int id, const std::string& text, int parentId, int row, int col);
    void draw_all() const;
    void printCommands() const;

    // === Check functions for Command classes ===
    bool isAvailableId(int id) const;
    bool isAvailableParentId(int parentId) const;
    bool isAvailableParentId_window(int parentId) const;
};

