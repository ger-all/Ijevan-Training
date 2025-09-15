#include "DrawCommand.hpp"
#include "WidgetManager.hpp"

bool DrawCommand::check() {
    return true;
}

void DrawCommand::execute() {
    WidgetManager::getInstance().draw_all();
}

