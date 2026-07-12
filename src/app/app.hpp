#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera/camera.hpp"
#include "geometry/mesh.hpp"
#include "scene/scene.hpp"
#include "ui/ui_manager.hpp"
#include "editor/editor_context.hpp"

struct App {
    // Dimensiones de la ventana
    const int mWidth = 800;
    const int mHeight = 600;
    float aspectRatio;

    SDL_Window* mWindow = nullptr;
    SDL_GLContext mGlContext = nullptr;

    bool mRunning = true;

    GLuint mShaderProgram = 0;
    Camera mCamera;

    glm::mat4 mProjection;
    glm::mat4 mView;

    Scene scene;

    ui::UIManager mUI;

    editor::EditorContext mContext;

    App();

    void init();
    void update(float dt);
    void render();
};