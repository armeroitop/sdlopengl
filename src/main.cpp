#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#include "app.hpp"
#include "camera.hpp"
#include "mesh.hpp"

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>


SDL_Event event;

App gApp;
//Mesh mesh1(-2.0f, 0.0f, 1.0f);
//Mesh mesh2(-4.0f, 0.0f, 1.0f);

void initialize(App* app) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    // Configuración OpenGL 3.3 Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    app->mWindow = SDL_CreateWindow(
        "Triángulo OpenGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        app->mWidth, app->mHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!app->mWindow) {
        std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }

    app->mGlContext = SDL_GL_CreateContext(app->mWindow);

    // Configuracion del mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);
    // SDL_WarpMouseInWindow(window, 400, 300); // Centrar el mouse en la ventana

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_DestroyWindow(app->mWindow);
        SDL_Quit();
        exit(-1);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}



GLuint createShaderProgram(const char* vertexSource, const char* fragmentSource) {
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

std::string loadShaderSource(const char* filename) {

    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo shader.");
    }

    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}

void createGraphicsPipeline() {
    std::string vertexShaderSource = loadShaderSource("shaders/vertex.glsl");
    std::string fragmentShaderSource = loadShaderSource("shaders/fragment.glsl");
    gApp.mShaderProgram = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
}

void inputHandling(App* app, float deltatime) {
    // don't shadow global mouse variables; we use SDL relative motion
    // Manejo de entradas (si es necesario)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app->mRunning = false;
        }

        if (event.type == SDL_MOUSEMOTION) {
            app->mCamera.mouseLook(event.motion.xrel, event.motion.yrel);
        }
    }

    SDL_PumpEvents();
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_ESCAPE]) {
        app->mRunning = false;
    }

    float speed = 1.2f;

    if (keyboardState[SDL_SCANCODE_UP]) {
        /* mesh1.m_uOffset += speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uOffset << std::endl; */
    }

    if (keyboardState[SDL_SCANCODE_DOWN]) {
        for (auto& mesh : app->mMeshes) {
            mesh.m_uOffset -= speed * deltatime;
            std::cout << "Offset: " << mesh.m_uOffset << std::endl;
        }
    }

    if (keyboardState[SDL_SCANCODE_LEFT]) {
        /* for (auto& mesh : app->mMeshes) {
            mesh.m_uRotation -= speed * deltatime;
            std::cout << "Rotation: " << mesh.m_uRotation << std::endl;
        } */
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        /* for (auto& mesh : app->mMeshes) {
            mesh.m_uRotation += speed * deltatime;
            std::cout << "Rotation: " << mesh.m_uRotation << std::endl;
        } */
    }

    if (keyboardState[SDL_SCANCODE_W]) {
        app->mCamera.moveForward(deltatime);
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        app->mCamera.moveBackward(deltatime);
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        app->mCamera.moveLeft(deltatime);
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        app->mCamera.moveRight(deltatime);
    }
}

void beginFrame() {

    // Activar test de profundidad
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  // estándar

    glEnable(GL_CULL_FACE); // opcional: cull front/back faces
    glCullFace(GL_BACK);    // opcional

    glViewport(0, 0, 800, 600);

    // Limpiar buffers
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void mainLoop() {
    Uint32 lastTime = SDL_GetTicks();

    // Bucle principal de la aplicación
    while (gApp.mRunning) {

        Uint32 currentTime = SDL_GetTicks();
        float deltatime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        inputHandling(&gApp, deltatime);

        for (auto& mesh : gApp.mMeshes) mesh.update(deltatime);
        beginFrame();
        gApp.render();

        SDL_GL_SwapWindow(gApp.mWindow);
    }
}

void cleanup(App* app) {

    glDeleteProgram(app->mShaderProgram);

    SDL_GL_DeleteContext(app->mGlContext);
    SDL_DestroyWindow(app->mWindow);
    SDL_Quit();
}

int main(int argc, char* argv []) {
    initialize(&gApp);

    createGraphicsPipeline();

    const std::vector<GLfloat> vertexPosition{
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // arriba, rojo
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // izquierda, verde
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // derecha, azul
         1.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // arriba, blanco
    };
    const std::vector<GLuint> indices{
        0, 1, 2, // primer triángulo
        3, 0, 2  // segundo triángulo
    };

    
    gApp.init();

    gApp.mMeshes.emplace_back(-2.0f, 0.0f, 1.0f);
    gApp.mMeshes.emplace_back(-4.0f, 0.0f, 1.0f);

    for (auto& mesh : gApp.mMeshes) {
        mesh.setVertexData(vertexPosition, indices);
        mesh.initialize();
    }

    mainLoop();

    for (auto& mesh : gApp.mMeshes) mesh.cleanup();

    cleanup(&gApp);

    return 0;
}
