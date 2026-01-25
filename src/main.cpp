#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>


SDL_GLContext glContext;
SDL_Window* window = nullptr;

bool running = true;
SDL_Event event;

GLuint gShaderProgram;
GLuint VAO, VBO, EBO;

GLint uniColor;

void initialize() {
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

    window = SDL_CreateWindow(
        "Triángulo OpenGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }

    glContext = SDL_GL_CreateContext(window);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

void vertexSpecification() {

    const std::vector<GLfloat> vertexPosition{
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // arriba, rojo
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // izquierda, verde
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // derecha, azul
         1.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  // arriba, blanco
    };

    GLuint indices[] = {
        0, 1, 2, // primer triángulo
        0, 2, 3  // segundo triángulo
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Buffer para los vértices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertexPosition.size() * sizeof(GLfloat),
        vertexPosition.data(),
        GL_STATIC_DRAW
    );

    // Buffer para los índices de triangulos
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // aquí el 1 es el location del atributo aColor

    // Desvincular VAO y VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    gShaderProgram = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
}

void inputHandling() {
    // Manejo de entradas (si es necesario)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
    }
}

void preDraw() {

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(gShaderProgram);
}

void draw() {
    // Lógica de dibujo (si es necesario)

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Alternatively, to draw a single triangle:
    // glDrawArrays(GL_TRIANGLES, 0, 3);
}

void mainLoop() {
    // Bucle principal de la aplicación
    while (running) {
        inputHandling();

        preDraw();

        draw();

        SDL_GL_SwapWindow(window);
    }
}

void cleanup() {
    // Limpieza de recursos (si es necesario)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(gShaderProgram);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    initialize();

    createGraphicsPipeline();

    vertexSpecification();

    mainLoop();

    cleanup();

    return 0;
}
