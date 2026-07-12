#pragma once
#include "editor/editor_context.hpp"
#include "scene/scene.hpp"


namespace ui {
class Hierarchy {
private:
    editor::EditorContext& mContext;
    Scene& mScene;
public:
    Hierarchy(editor::EditorContext& context, Scene& scene);
    ~Hierarchy();
    void draw();
};



} // namespace ui

