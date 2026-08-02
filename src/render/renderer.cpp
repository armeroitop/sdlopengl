#include "renderer.hpp"


#include <iostream>

#include <fstream>

namespace render {

Renderer::Renderer(/* args */) {
}

Renderer::~Renderer() {
}

void Renderer::render(Scene& scene, Camera& camera, const ui::Viewport& viewport) {

    mShader.use();

    mProjection = camera.getPerspectiveMatrix(viewport.getAspectRatio());
    mView = camera.getViewMatrix();

    mShader.setMat4("view", mView);
    mShader.setMat4("perspective", mProjection);

    // Dibujar objetos
    for (auto& object : scene.getObjects()) {

        mShader.setMat4("model", object.getModelMatrix());
        object.draw();
    }
}

void Renderer::init() {

    if (!mShader.load("shaders/vertex.glsl", "shaders/fragment.glsl")) {
        std::cerr << "No se ha podido iniciar el Shader. \n";
        exit(EXIT_FAILURE);
    }
}

void Renderer::beginFrame(SDL_Window* window) {

    // Activar test de profundidad
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  // estándar

    glEnable(GL_CULL_FACE); // opcional: cull front/back faces
    glCullFace(GL_BACK);    // opcional

    int w, h;
    SDL_GL_GetDrawableSize(window, &w, &h);

    glViewport(0, 0, w, h);

    // Limpiar buffers
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



} // namespace render
