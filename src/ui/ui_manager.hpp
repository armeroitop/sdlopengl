#pragma once 

#include "ui/toolbar.hpp"
#include "ui/hierarchy.hpp"
#include "ui/inspector.hpp"
#include "ui/viewport.hpp"
#include "ui/dock_layout.hpp"

namespace ui {
class UIManager {

private:
    editor::EditorContext& mContext;
    Scene& mScene;
    DockLayout mDockLayout;
    Toolbar mToolbar;
    Hierarchy mHierarchy;
    Inspector mInspector;
    Viewport mViewport;

public:
    UIManager(editor::EditorContext& context , Scene& scene);
    ~UIManager();
    void draw();

    
};
} // namespace ui




