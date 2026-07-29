#pragma once

#include "editor/editor_context.hpp"
#include "scene/scene.hpp"


namespace ui {

class Viewport {

private:
    editor::EditorContext& mContext;
    Scene& mScene;

public:
    Viewport(editor::EditorContext& context, Scene& scene);
    ~Viewport();

    void draw();
};

} // namespace ui