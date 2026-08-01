#include "renderer.hpp"


#include <iostream>

#include <fstream>

namespace render {

Renderer::Renderer(/* args */) {
}

Renderer::~Renderer() {
}

void Renderer::render(Scene& scene, Camera& camera, const ui::Viewport& viewport) {

    glUseProgram(mShaderProgram);

    mProjection = camera.getPerspectiveMatrix(viewport.getAspectRatio());
    mView = camera.getViewMatrix();

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

    // Dibujar objetos
    for (auto& object : scene.getObjects()) {

        if (modelLoc != -1) {
            glUniformMatrix4fv(
                modelLoc,
                1,
                GL_FALSE,
                glm::value_ptr(object.getModelMatrix())
            );
        } else {
            std::cerr << "Warning: uniform model no encontrada en el shader\n";
            exit(EXIT_FAILURE);
        }
        object.draw();
    }
}

std::string Renderer::loadShaderSource(const char* filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo shader.");
    }

    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}

GLuint Renderer::createShaderProgram(const char* vertexSource, const char* fragmentSource) {
    // Crear y compilar shaders, luego enlazarlos en un programa

    auto compileShader = [](GLenum type, const char* source) -> GLuint {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Error compilando "
                << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                << " shader:\n" << infoLog << std::endl;
            glDeleteShader(shader);
            return 0;
        }
        return shader;
        };

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (!vertexShader || !fragmentShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::cerr << "Error enlazando programa:\n" << infoLog << std::endl;
        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

#ifdef _DEBUG
    glValidateProgram(program);
#endif

    return program;
}

void Renderer::init() {

    std::string vertexShaderSource = loadShaderSource("shaders/vertex.glsl");
    std::string fragmentShaderSource = loadShaderSource("shaders/fragment.glsl");

    setShaderProgram(createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str()));
}

void Renderer::setShaderProgram(GLuint shaderProgram) {
    mShaderProgram = shaderProgram;
}

GLuint Renderer::getShaderProgram() const {
    return mShaderProgram;
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
