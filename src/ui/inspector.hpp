#pragma once

#include "editor/editor_context.hpp"
#include "scene/scene.hpp"


namespace ui {

class Inspector {
private:
    editor::EditorContext& mContext;
    Scene& mScene;
public:
    Inspector(editor::EditorContext& context, Scene& scene);
    ~Inspector();

    void draw();
};
} // namespace ui




