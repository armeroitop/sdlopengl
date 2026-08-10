#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera/camera.hpp"
#include "camera/camera_controller.hpp"
#include "geometry/mesh.hpp"
#include "scene/scene.hpp"
#include "ui/ui_manager.hpp"
#include "editor/editor_context.hpp"
#include "render/renderer.hpp"
#include "input/input.hpp"

struct App {
    // Dimensiones de la ventana
    const int mWidth = 1280;
    const int mHeight = 720;
    float aspectRatio;

    SDL_Window* mWindow = nullptr;
    SDL_GLContext mGlContext = nullptr;

    bool mRunning = true;
    
    Camera mCamera;
    camera::CameraController mCameraController;
    input::Input mInput;
    u_int32_t mCurrentSelectedObjectId = 0;
    u_int32_t mLastSelectedObjectId = 0;

    Scene mScene;
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

    void initializeRenderer();
};