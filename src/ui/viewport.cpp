#include "viewport.hpp"



namespace ui {
Viewport::Viewport(editor::EditorContext& context, Scene& scene)
    :mContext(context), mScene(scene) {
}

Viewport::~Viewport() {
}

void Viewport::draw() {
    ImGui::Begin("Viewport");
    ImVec2 size = ImGui::GetContentRegionAvail();

    // Si el panel no tiene tamaño, no hacemos nada.
    if (size.x <= 0 || size.y <= 0) {
        ImGui::End();
        return;
    }

    if (size.x != mSize.x || size.y != mSize.y) {
        mSize = size;

        mFramebuffer.resize(
            (int)mSize.x,
            (int)mSize.y
        );
    }

    ImGui::Image(
        (ImTextureID)(intptr_t)mFramebuffer.getTexture(),
        mSize,
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    ImGui::Text("Viewport");
    ImGui::Separator();

    ImGui::Text("Size: %.0f x %.0f", size.x, size.y);
    ImGui::End();
}

void Viewport::update() {
}

void Viewport::begin() {
    ImGui::Begin("Viewport");

    ImVec2 size = ImGui::GetContentRegionAvail();

    if (size.x > 0 &&
        size.y > 0 &&
        (size.x != mSize.x || size.y != mSize.y)) {
        mSize = size;

        mFramebuffer.resize(
            (int)mSize.x,
            (int)mSize.y
        );
    }
}

void Viewport::beginRender() {
    if (mFramebuffer.width() == 0 || mFramebuffer.height() == 0) {
        return;
    }

    mFramebuffer.bind();

    glViewport(
        0,
        0,
        mFramebuffer.width(),
        mFramebuffer.height()
    );

    printf("%d x %d\n", mFramebuffer.width(), mFramebuffer.height());

    // limpieza de color y profundidad
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Viewport::endRender() {
    if (mFramebuffer.width() == 0 || mFramebuffer.height() == 0) {
        return;
    }

    mFramebuffer.unbind();
}

void Viewport::end() {
    if (mFramebuffer.getTexture() != 0) {
        ImGui::Image(
            (ImTextureID)(intptr_t)mFramebuffer.getTexture(),
            mSize,
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
    }

    ImGui::Text("Size: %.0f x %.0f", mSize.x, mSize.y);

    ImGui::End();
}

float Viewport::getAspectRatio() const {
    if (mSize.y <= 0.0f) {
        return 1.0f;
    }

    return mSize.x / mSize.y;
}

int Viewport::getWidth() const {
    return static_cast<int>(mSize.x);
}

int Viewport::getHeight() const {
    return static_cast<int>(mSize.y);
}

} // namespace ui
