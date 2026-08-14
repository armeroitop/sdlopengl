#include "app.hpp"
#include "geometry/mesh.hpp"
#include "scene/object.hpp"

#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/gtx/string_cast.hpp>


App::App()
    : mUI(mContext, mScene, mCamera) {
}

void App::init() {
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

    mWindow = SDL_CreateWindow(
        "Triángulo OpenGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        mWidth, mHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
    );

    if (!mWindow) {
        std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }

    mGlContext = SDL_GL_CreateContext(mWindow);

    // Configuracion del mouse
    SDL_SetRelativeMouseMode(SDL_FALSE);
    // SDL_WarpMouseInWindow(window, 400, 300); // Centrar el mouse en la ventana

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_DestroyWindow(mWindow);
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
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(mWindow, mGlContext);
    ImGui_ImplOpenGL3_Init();

    // Setup estilos de imgui
    ImGuiStyle& style = ImGui::GetStyle();
    //style.WindowPadding = ImVec2(0, 0);
    //style.DisplayWindowPadding = ImVec2(0, 0);
    //style.DisplaySafeAreaPadding = ImVec2(0, 0);
    //style.WindowBorderSize = 0.0f;
    //style.WindowRounding = 0.0f;

    // Inicializar el render
    mRenderer.init();
}

void App::update(float dt) {
    mScene.update(dt);

    // Actualizamo el mPivot de la camara a la posición del objeto seleccionado
    mCurrentSelectedObjectId = mContext.getSelectedObjectId();
    if (mCurrentSelectedObjectId != mLastSelectedObjectId) {
        // TODO Desacoplar la selección de la cámara.
        // Actualmente el pivot se mueve al objeto seleccionado para facilitar
        // el desarrollo de orbit(). En la versión definitiva, seleccionar un
        // objeto NO modificará el pivot automáticamente.

        if (Object* object = mScene.findObject(mCurrentSelectedObjectId)) {
            mCamera.setPivot(object->getTransform().position);

            mLastSelectedObjectId = mCurrentSelectedObjectId;
        }
    }

    mUI.update(mInput);
}

void App::render() {
    mRenderer.render(mScene, mCamera, mUI.getViewport(), mContext);
}

void App::run() {
    Uint32 lastTime = SDL_GetTicks();

    // Bucle principal de la aplicación
    while (mRunning) {

        // (You should discard mouse/keyboard messages in your game/engine when io.WantCaptureMouse/io.WantCaptureKeyboard are set.)
        // (After event loop)
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        //ImGui::ShowDemoWindow(); // Show demo window! :)

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;


        processEvents();
        //updateInputs(deltaTime); // para eliminar
        mCameraController.update(mCamera, mInput, deltaTime);

        //for (auto& mesh : gApp.mMeshes) mesh.update(deltatime);
        //mScene.update(deltaTime);
        update(deltaTime);

        mRenderer.beginFrame(mWindow);

        mUI.begin();

        mUI.beginViewportRender();

        render();

        mUI.endViewportRender();

        mUI.end();


        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls SDL_GL_SwapWindow() etc.)

        SDL_GL_SwapWindow(mWindow);
    }
}

void App::shutdown() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(mGlContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void App::processEvents() {

    mInput.reset();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // (Where your code calls SDL_PollEvent())
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend

        if (event.type == SDL_QUIT) {
            mRunning = false;
        }

        if (event.type == SDL_MOUSEMOTION) {
            mInput.mouseDelta.x = event.motion.xrel;
            mInput.mouseDelta.y = event.motion.yrel;
        }

        if (event.type == SDL_MOUSEWHEEL) {
            mInput.wheelDelta = event.wheel.preciseY;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                mInput.leftMouseDown = true;
            }
        }
    }

    // Teclado
    const uint8_t* keyboardState = SDL_GetKeyboardState(NULL);
    mInput.keyA = keyboardState[SDL_SCANCODE_A];
    mInput.keyW = keyboardState[SDL_SCANCODE_W];
    mInput.keyS = keyboardState[SDL_SCANCODE_S];
    mInput.keyD = keyboardState[SDL_SCANCODE_D];
    mInput.keyAlt = keyboardState[SDL_SCANCODE_LALT];

    // Mouse
    mInput.leftMouse = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
    mInput.middleMouse = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
    mInput.rightMouse = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT));

    SDL_GetMouseState(&mInput.mouseAbsolutePosition.x, &mInput.mouseAbsolutePosition.y);


}


