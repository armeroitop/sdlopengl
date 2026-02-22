#pragma once
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"

struct App {
    // Dimensiones de la ventana
    const int mWidth = 800;
    const int mHeight = 600;

    float aspectRatio = mWidth / static_cast<float>(mHeight);

    SDL_Window* mWindow = nullptr;
    SDL_GLContext mGlContext = nullptr;

    bool mRunning = true;

    GLuint mShaderProgram = 0;
    Camera mCamera;
};