#include "input.hpp"

#include <SDL2/SDL.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

namespace input {
Input::Input() {
}
Input::~Input() {
}
void Input::reset() {

    keyFDown = false;
    keyFUp = false;

    mouseDelta.x = 0.0f;
    mouseDelta.y = 0.0f;
    wheelDelta = 0.0f;

    leftMouseDown = false;
}
void Input::update() {

    // 1. Preparar el estado del frame
    reset();
    quitRequested = false;

    // 2. Procesar eventos
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // (Where your code calls SDL_PollEvent())
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend

        // Sistema
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Teclado
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_F && !event.key.repeat) {
                keyFDown = true;
            }
        }

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                keyFUp = true;
            }
        }

        // Mouse
        if (event.type == SDL_MOUSEMOTION) {
            mouseDelta.x += event.motion.xrel;
            mouseDelta.y += event.motion.yrel;
        }

        if (event.type == SDL_MOUSEWHEEL) {
            wheelDelta += event.wheel.preciseY;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                leftMouseDown = true;
            }
        }
    }

    // 3. Actualizar estados
    // Teclado
    const uint8_t* keyboardState = SDL_GetKeyboardState(NULL);
    keyA = keyboardState[SDL_SCANCODE_A];
    keyW = keyboardState[SDL_SCANCODE_W];
    keyS = keyboardState[SDL_SCANCODE_S];
    keyD = keyboardState[SDL_SCANCODE_D];
    keyF = keyboardState[SDL_SCANCODE_F];
    keyAlt = keyboardState[SDL_SCANCODE_LALT];

    // Mouse
    const Uint32 mouseState = SDL_GetMouseState(
        &mouseAbsolutePosition.x,
        &mouseAbsolutePosition.y
    );

    leftMouse = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
    middleMouse = mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE);
    rightMouse = mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT);

}
} // namespace input

