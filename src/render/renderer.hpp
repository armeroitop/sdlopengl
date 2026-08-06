#pragma once
#include <glad/glad.h>

#include "scene/scene.hpp"
#include "camera/camera.hpp"
#include "ui/viewport.hpp"
#include "shader.hpp"
#include "editor/editor_context.hpp"
#include "grid.hpp"

namespace render {

class Renderer {

private:
    //GLuint mShaderProgram = 0;
    glm::mat4 mProjection;
    glm::mat4 mView;

    Shader mShader;
    Grid mGrid;

public:
    Renderer(/* args */);
    ~Renderer();

    void render(
        Scene& scene,
        Camera& camera,
        const ui::Viewport& viewport,
        const editor::EditorContext& context
    );

    //std::string loadShaderSource(const char* filename);
    //GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource);
    void init();
    //void setShaderProgram(GLuint shaderProgram);
    //GLuint getShaderProgram() const;
    void beginFrame(SDL_Window* window);
};



} // namespace render
