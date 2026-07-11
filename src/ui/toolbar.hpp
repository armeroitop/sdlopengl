#pragma once

#include "editor/editor_context.hpp"
#include "scene/scene.hpp"


namespace ui {

class Toolbar {

private:
    editor::EditorContext& mContext;
    Scene& mScene;

public:
    Toolbar(editor::EditorContext& context, Scene& scene);
    ~Toolbar();

    void draw();
};

} // namespace ui


