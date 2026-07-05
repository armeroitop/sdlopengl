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
//#include "mesh.hpp"
#include "geometry/mesh.hpp"

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
    SDL_SetRelativeMouseMode(SDL_FALSE);
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

    // Inicializar ImGui
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(app->mWindow, app->mGlContext);
    ImGui_ImplOpenGL3_Init();
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

void processEvents(App* app){

    ImGuiIO& io = ImGui::GetIO();
     io.MouseDrawCursor = true;
   
    while (SDL_PollEvent(&event)) {
        // (Where your code calls SDL_PollEvent())
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend

        if (event.type == SDL_QUIT) {
            app->mRunning = false;
        }

        if (!io.WantCaptureMouse 
            && event.type == SDL_MOUSEMOTION) {
           
            app->mCamera.mouseLook(event.motion.xrel, event.motion.yrel);

            //SDL_SetRelativeMouseMode(SDL_TRUE);
           
            
        } else {
            //io.MouseDrawCursor = true;
            //SDL_SetRelativeMouseMode(SDL_FALSE);
        }

    }
}

void updateInputs(App* app, float deltatime) {

    ImGuiIO& io = ImGui::GetIO();

    SDL_PumpEvents();
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_ESCAPE]) {
        app->mRunning = false;
    }

    // Si ImGui está usando el teclado, salimos aquí
    if (io.WantCaptureKeyboard) {
        return;
    }

    float speed = 1.2f;

    if (keyboardState[SDL_SCANCODE_UP]) {
        /* mesh1.m_uOffset += speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uOffset << std::endl; */
    }

    if (keyboardState[SDL_SCANCODE_DOWN]) {
        /* for (auto& mesh : app->mMeshes) {
            mesh.m_uOffset -= speed * deltatime;
            std::cout << "Offset: " << mesh.m_uOffset << std::endl;
        } */
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

void inputHandling_bck(App* app, float deltatime) {

    ImGuiIO& io = ImGui::GetIO();
    // don't shadow global mouse variables; we use SDL relative motion
    // Manejo de entradas (si es necesario)
    while (SDL_PollEvent(&event)) {
        // (Where your code calls SDL_PollEvent())
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend

        if (event.type == SDL_QUIT) {
            app->mRunning = false;
        }

        if (!io.WantCaptureMouse) {
            if (event.type == SDL_MOUSEMOTION) {
                app->mCamera.mouseLook(event.motion.xrel, event.motion.yrel);
            }
        }
    }

    SDL_PumpEvents();
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_ESCAPE]) {
        app->mRunning = false;
    }

        // Si ImGui está usando el teclado, salimos aquí
    if (io.WantCaptureKeyboard) {
        return;
    }

    float speed = 1.2f;

    if (keyboardState[SDL_SCANCODE_UP]) {
        /* mesh1.m_uOffset += speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uOffset << std::endl; */
    }

    if (keyboardState[SDL_SCANCODE_DOWN]) {
        /* for (auto& mesh : app->mMeshes) {
            mesh.m_uOffset -= speed * deltatime;
            std::cout << "Offset: " << mesh.m_uOffset << std::endl;
        } */
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
        
        // (You should discard mouse/keyboard messages in your game/engine when io.WantCaptureMouse/io.WantCaptureKeyboard are set.)
        // (After event loop)
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)

        Uint32 currentTime = SDL_GetTicks();
        float deltatime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        processEvents(&gApp);
        updateInputs(&gApp, deltatime);

        //for (auto& mesh : gApp.mMeshes) mesh.update(deltatime);
        gApp.scene.update(deltatime);
        
        beginFrame();
        gApp.render();

        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls SDL_GL_SwapWindow() etc.)

        SDL_GL_SwapWindow(gApp.mWindow);
    }
}

void cleanup(App* app) {

    glDeleteProgram(app->mShaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

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

    app::geometry::Mesh mesh(vertexPosition, indices);

    Transform t1;
    t1.position = glm::vec3(0.0f, 0.0f, -2.0f);

    Transform t2;
    t2.position = glm::vec3(0.0f, 0.0f, -4.0f);

    Object obj1(mesh, t1);
    Object obj2(mesh, t2);
    
    gApp.init();
    gApp.scene.addObject(obj1);
    gApp.scene.addObject(obj2);

    //gApp.mMeshes.emplace_back(-2.0f, 0.0f, 1.0f);
    //gApp.mMeshes.emplace_back(-4.0f, 0.0f, 1.0f);

    /* for (auto& mesh : gApp.mMeshes) {
        mesh.setVertexData(vertexPosition, indices);
        mesh.initialize();
    } */

    mainLoop();

    //for (auto& mesh : gApp.mMeshes) mesh.cleanup();

    cleanup(&gApp);

    return 0;
}
