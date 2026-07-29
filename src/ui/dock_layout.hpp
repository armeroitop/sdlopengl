#pragma once
#include <imgui.h>

namespace ui {
class DockLayout {

private:

    void buildDefaultLayout();
    void beginDockSpace();

    bool mInitialized = false;
    ImGuiID mDockspaceID = 0;

public:
    DockLayout(/* args */);
    ~DockLayout();

    void begin();
    void end();
};
} // namespace ui


