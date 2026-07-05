#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "geometry/mesh.hpp"
#include "scene/scene.hpp"

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

    //std::vector<Mesh> mMeshes;
    Scene scene;

    void init();
    void update(float dt);
    void render();
};