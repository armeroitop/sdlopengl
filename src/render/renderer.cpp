#include "renderer.hpp"


#include <iostream>

#include <fstream>

namespace render {

Renderer::Renderer(/* args */) {
}

Renderer::~Renderer() {
}

void Renderer::render(Scene& scene, Camera& camera, const ui::Viewport& viewport, const editor::EditorContext& context) {

    mShader.use();

    mProjection = camera.getPerspectiveMatrix(viewport.getAspectRatio());
    mView = camera.getViewMatrix();

    mShader.setMat4("view", mView);
    mShader.setMat4("perspective", mProjection);

    // Dibujamos el Grid
    mShader.setMat4("model", glm::mat4(1.0f));
    mShader.setBool("useOverrideColor", false); // Lo dibujamos con color normal
    mGrid.draw();

    // Dibujar objetos
    for (auto& object : scene.getObjects()) {
        const bool isSelected =
            object.getId() == context.getSelectedObjectId();

        mShader.setMat4("model", object.getModelMatrix());

        // Siempre dibujamos el objeto sólido
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        mShader.setBool("useOverrideColor", false);
        object.draw();

        if (isSelected) {

            // Después dibujamos el wireframe encima
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            mShader.setBool("useOverrideColor", true); // usamos el color de seleccionado
            mShader.setVec3("overrideColor", glm::vec3(1.0f, 0.6f, 0.0f));
            glLineWidth(2.0f);

            object.draw();

            // Restauramos el estado
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glLineWidth(1.0f);
            mShader.setBool("useOverrideColor", false);
        }
    }
}

void Renderer::init() {

    if (!mShader.load("shaders/vertex.glsl", "shaders/fragment.glsl")) {
        std::cerr << "No se ha podido iniciar el Shader. \n";
        exit(EXIT_FAILURE);
    }

    mGrid.init();
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
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



} // namespace render
