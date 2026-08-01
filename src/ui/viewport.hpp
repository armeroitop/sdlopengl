#pragma once
#include <glad/glad.h>
#include <imgui.h>

#include "editor/editor_context.hpp"
#include "scene/scene.hpp"
#include "render/framebuffer.hpp"


namespace ui {

class Viewport {

private:
    editor::EditorContext& mContext;
    Scene& mScene;
    render::Framebuffer mFramebuffer;

    ImVec2 mSize;

public:
    Viewport(editor::EditorContext& context, Scene& scene);
    ~Viewport();

    void draw();
    void update();

    void begin();
    void beginRender();
    void endRender();

    void end();


    float getAspectRatio() const;
    int getWidth() const;
    int getHeight() const;
};

} // namespace ui