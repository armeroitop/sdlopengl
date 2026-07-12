#pragma once 

#include "ui/toolbar.hpp"
#include "ui/hierarchy.hpp"

namespace ui {
class UIManager {

private:
    editor::EditorContext& mContext;
    Scene& mScene;
    Toolbar mToolbar;
    Hierarchy mHierarchy;

public:
    UIManager(editor::EditorContext& context , Scene& scene);
    ~UIManager();
    void draw();

     //void drawHierarchy();
};
} // namespace ui




