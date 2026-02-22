#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>

#include "camera.hpp"


SDL_GLContext glContext;
SDL_Window* window = nullptr;
bool running = true;
GLuint gShaderProgram;


SDL_Event event;
GLuint VAO, VBO, EBO;

GLint uniColor;

GLfloat g_uOffset_x = 0.0f;
GLfloat g_uOffset_y = -2.0f;
int mouseX = 400;
int mouseY = 300;

GLint g_modelLoc;
GLint g_perspectiveLoc;


GLint g_viewLoc;

struct App {
    // Dimensiones de la ventana
    const int mWidth = 800;
    const int mHeight = 600;

    SDL_Window* mWindow = nullptr;
    SDL_GLContext mGlContext = nullptr;

    bool mRunning = true;

    GLuint mShaderProgram = 0;
    Camera mCamera;
};

struct Mesh3D {
    App* app = nullptr;

    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;

    GLint mModelLoc;
    GLint mPerspectiveLoc;
    GLint mViewLoc;

    float m_uOffset = -2.0f;
    float m_uRotation = 0.0f;
    float m_uScale = 1.0f;

    glm::mat4 model;
    glm::mat4 perspective;
    glm::mat4 view;

    Mesh3D(App* app, float uOffset, float uRotation, float uScale);
    ~Mesh3D();
    void initialize();
    void update(float deltatime);
    void setUniforms();
    void draw();
    void cleanup();
};

Mesh3D::Mesh3D(App* app, float uOffset, float uRotation, float uScale)
    : app(app), m_uOffset(uOffset), m_uRotation(uRotation), m_uScale(uScale) {
}
Mesh3D::~Mesh3D() {
    // Destructor por defecto
}

void Mesh3D::initialize() {
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

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Buffer para los vértices
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertexPosition.size() * sizeof(GLfloat),
        vertexPosition.data(),
        GL_STATIC_DRAW
    );

    // Buffer para los índices de triangulos
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(GLuint),
        indices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // aquí el 1 es el location del atributo aColor

    // Desvincular VAO y VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh3D::update(float deltatime) {
    // Actualización de la lógica del mesh (si es necesario)
    model = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(0.0f, 0.0f, m_uOffset)
    );

    model = glm::rotate(
        model,
        glm::radians(m_uRotation * 10.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    model = glm::scale(
        model,
        glm::vec3(m_uScale, m_uScale, m_uScale)
    );

    perspective = glm::perspective(
        glm::radians(45.0f),
        app->mWidth / (float)app->mHeight,
        0.1f,
        100.0f
    );

    view = app->mCamera.getViewMatrix();

    glUseProgram(app->mShaderProgram);
}

void Mesh3D::setUniforms() {
    // Configuración de uniformes específicos del mesh (si es necesario)

    mModelLoc       = glGetUniformLocation(app->mShaderProgram, "model");
    mPerspectiveLoc = glGetUniformLocation(app->mShaderProgram, "perspective");
    mViewLoc        = glGetUniformLocation(app->mShaderProgram, "view");

    if (mModelLoc == -1) {
        std::cerr << "Warning: uniform model no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    } else {
        glUniformMatrix4fv(mModelLoc, 1, GL_FALSE, glm::value_ptr(model));
    }

    if (mPerspectiveLoc == -1) {
        std::cerr << "Warning: uniform perspective no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    } else {
        glUniformMatrix4fv(mPerspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
    }

    if (mViewLoc == -1) {
        std::cerr << "Warning: uniform view no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    } else {
        glUniformMatrix4fv(mViewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
}

void Mesh3D::draw() {
    // Lógica de dibujo del mesh
    glUseProgram(app->mShaderProgram);
    glBindVertexArray(mVAO);
    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        0
    );
}

void Mesh3D::cleanup() {
    // Limpieza de recursos (si es necesario)
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

App gApp;
Mesh3D mesh1(&gApp, -2.0f, 0.0f, 1.0f);
Mesh3D mesh2(&gApp, -4.0f, 0.0f, 1.0f);

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

void vertexSpecification(Mesh3D* mesh) {

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

    glGenVertexArrays(1, &mesh->mVAO);
    glBindVertexArray(mesh->mVAO);

    // Buffer para los vértices
    glGenBuffers(1, &mesh->mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->mVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertexPosition.size() * sizeof(GLfloat),
        vertexPosition.data(),
        GL_STATIC_DRAW
    );

    // Buffer para los índices de triangulos
    glGenBuffers(1, &mesh->mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(GLuint),
        indices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // aquí el 1 es el location del atributo aColor

    // Desvincular VAO y VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    g_modelLoc = glGetUniformLocation(gApp.mShaderProgram, "model");
    g_perspectiveLoc = glGetUniformLocation(gApp.mShaderProgram, "perspective");
    g_viewLoc = glGetUniformLocation(gApp.mShaderProgram, "view");
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
        mesh1.m_uOffset += speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uOffset << std::endl;
    }

    if (keyboardState[SDL_SCANCODE_DOWN]) {
        mesh1.m_uOffset -= speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uOffset << std::endl;
    }

    if (keyboardState[SDL_SCANCODE_LEFT]) {
        mesh1.m_uRotation -= speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uRotation << std::endl;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        mesh1.m_uRotation += speed * deltatime;
        std::cout << "Offset: " << mesh1.m_uRotation << std::endl;
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

void preDraw() {

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    /*
    glm::mat4 model = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(0.0f, 0.0f, gMesh3D.m_uOffset)
    );

    model = glm::rotate(
        model,
        glm::radians(gMesh3D.m_uRotation * 10.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    model = glm::scale(
        model,
        glm::vec3(gMesh3D.m_uScale, gMesh3D.m_uScale, gMesh3D.m_uScale)
    );

    glm::mat4 perspective = glm::perspective(
        glm::radians(45.0f),
        gApp.mWidth / (float)gApp.mHeight,
        0.1f,
        100.0f
    );

    glm::mat4 view = gCamera.getViewMatrix();

    glUseProgram(gApp.mShaderProgram);

    if (g_modelLoc == -1) {
        std::cerr << "Warning: uniform model no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    } else {
        glUniformMatrix4fv(g_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    }

    if (g_perspectiveLoc == -1) {
        std::cerr << "Warning: uniform perspective no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    } else {
        glUniformMatrix4fv(g_perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));
    }

    if (g_viewLoc == -1) {
        std::cerr << "Warning: uniform view no encontrada en el shader\n";
        exit(EXIT_FAILURE);
    } else {
        glUniformMatrix4fv(g_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    */
}

void draw() {
    // Lógica de dibujo (si es necesario)

    /* glBindVertexArray(gMesh3D.mVAO);
    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        0
    ); */

    // Alternatively, to draw a single triangle:
    // glDrawArrays(GL_TRIANGLES, 0, 3);
}

void mainLoop() {
    Uint32 lastTime = SDL_GetTicks();

    // Bucle principal de la aplicación
    while (gApp.mRunning) {

        Uint32 currentTime = SDL_GetTicks();
        float deltatime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        inputHandling(&gApp, deltatime);

        preDraw();
        draw();
        mesh1.update(deltatime);
        mesh2.update(deltatime);
        
        mesh1.setUniforms();
        mesh1.draw();
        
        mesh2.setUniforms();
        mesh2.draw();

        SDL_GL_SwapWindow(gApp.mWindow);
    }
}

void cleanup(App* app) {
    // Limpieza de recursos (si es necesario)
    /* glDeleteVertexArrays(1, &gMesh3D.mVAO);
    glDeleteBuffers(1, &gMesh3D.mVBO);
    glDeleteBuffers(1, &gMesh3D.mEBO); */
    glDeleteProgram(app->mShaderProgram);

    SDL_GL_DeleteContext(app->mGlContext);
    SDL_DestroyWindow(app->mWindow);
    SDL_Quit();
}

int main(int argc, char* argv []) {
    initialize(&gApp);

    createGraphicsPipeline();

    //vertexSpecification(&gMesh3D);
    mesh1.initialize();
    mesh2.initialize();

    mainLoop();

    mesh1.cleanup();
    mesh2.cleanup();
    cleanup(&gApp);

    return 0;
}
