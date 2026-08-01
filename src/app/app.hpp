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
#include "render/renderer.hpp"

struct App {
    // Dimensiones de la ventana
    const int mWidth = 1280;
    const int mHeight = 720;
    float aspectRatio;

    SDL_Window* mWindow = nullptr;
    SDL_GLContext mGlContext = nullptr;

    bool mRunning = true;

    //GLuint mShaderProgram = 0;
    Camera mCamera;

    //glm::mat4 mProjection;
    //glm::mat4 mView;

    Scene scene;
    editor::EditorContext mContext;

    ui::UIManager mUI;

    render::Renderer mRenderer;


    App();

    void init();
    void update(float dt);
    void render();

    void run();
    void shutdown();
    void processEvents();
    void renderFrame();
    void updateInputs(float deltaTime);

    void initializeRenderer();
};