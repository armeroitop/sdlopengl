#include "app.hpp"
#include "mesh.hpp"

#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>


void App::init() {
    aspectRatio = mWidth / static_cast<float>(mHeight);
}

void App::update(float dt) {
}

void App::render() {
    glUseProgram(mShaderProgram);
    mProjection = mCamera.getPerspectiveMatrix(aspectRatio);
    mView = mCamera.getViewMatrix();

    GLint modelLoc = glGetUniformLocation(mShaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(mShaderProgram, "view");
    GLint projLoc = glGetUniformLocation(mShaderProgram, "perspective");


    if (projLoc != -1) {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjection));
    } else {
        std::cerr << "Warning: uniform perspective no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    }

    if (viewLoc != -1) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));
    } else {
        std::cerr << "Warning: uniform view no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    }

    for (auto& mesh : mMeshes) {
        if (modelLoc != -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh.getModelMatrix()));
        } else {
            std::cerr << "Warning: uniform model no encontrada en el shader\n";
            exit(EXIT_FAILURE);
        }

        mesh.draw();
    }
}