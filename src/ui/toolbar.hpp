#pragma once

#include <imgui.h>
#include "editor/editor_context.hpp"
#include "scene/scene.hpp"


namespace ui {

class Toolbar {

private:
    editor::EditorContext& mContext;
    Scene& mScene;
    void addButton(const char* label, editor::Tool tool);
    void addTransformModeButton(const char* label, editor::TransformMode mode);
    ImVec4 getButtonColor(bool selected) const;

public:
    Toolbar(editor::EditorContext& context, Scene& scene);
    ~Toolbar();

    void draw();
};

} // namespace ui


