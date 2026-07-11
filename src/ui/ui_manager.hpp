#pragma once 

#include "ui/toolbar.hpp"

namespace ui {
class UIManager {

private:
    editor::EditorContext& mContext;
    Toolbar mToolbar;
public:
    UIManager(editor::EditorContext& context , Scene& scene);
    ~UIManager();
    void draw();
};
} // namespace ui




