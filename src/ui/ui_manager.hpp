#pragma once 

#include "ui/toolbar.hpp"
#include "ui/hierarchy.hpp"
#include "ui/inspector.hpp"

namespace ui {
class UIManager {

private:
    editor::EditorContext& mContext;
    Scene& mScene;
    Toolbar mToolbar;
    Hierarchy mHierarchy;
    Inspector mInspector;

public:
    UIManager(editor::EditorContext& context , Scene& scene);
    ~UIManager();
    void draw();

     //void drawHierarchy();
};
} // namespace ui




