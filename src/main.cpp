#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>

// Vertex Shader
const char* vertexShaderSource = R"glsl(
#version 330 core
in vec3 aPos;
in vec3 aColor;
out vec3 ourColor;
    
void main()
{
    ourColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}
)glsl";

// Fragment Shader
const char* fragmentShaderSource = R"glsl(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)glsl";

SDL_GLContext glContext;
SDL_Window* window = nullptr;

bool running = true;
SDL_Event event;

unsigned int shaderProgram;
unsigned int VAO, VBO;

GLint uniColor;

void initialize() {
    // Inicializaciones necesarias (si es necesario)
     // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    // Configuración OpenGL 3.3 Core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("Triángulo OpenGL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

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

    // Shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);



    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Triángulo
    float vertices[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Buffer para los índices de triangulos
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configuración de los atributos de los vértices
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "aColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Desvincular VAO y VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

   
}

void inputHandling() {
    // Manejo de entradas (si es necesario)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
    }
}

void preDraw() {
    // Configuraciones previas al dibujo (si es necesario)
}

void draw() {
    // Lógica de dibujo (si es necesario)
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // Alternatively, to draw a single triangle:
    // glDrawArrays(GL_TRIANGLES, 0, 3);
}

void mainLoop() {
    // Bucle principal de la aplicación (si es necesario)

    while (running) {
        inputHandling();

        preDraw();

        draw();

        SDL_GL_SwapWindow(window);
    }
}

void cleanup() {
    // Limpieza de recursos (si es necesario)
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    initialize();

    mainLoop();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    cleanup();
    return 0;
}
