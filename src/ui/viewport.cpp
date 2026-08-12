#include "viewport.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <optional>


namespace ui {
Viewport::Viewport(editor::EditorContext& context, Scene& scene, Camera& camera)
    :mContext(context), mScene(scene), mCamera(camera) {
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

    //ImGui::Text("Size: %.0f x %.0f", size.x, size.y);
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

    mImagePos = ImGui::GetCursorScreenPos();
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

    //printf("%d x %d\n", mFramebuffer.width(), mFramebuffer.height());

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

    // Configuración de ImGuizmo
    ImGuizmo::SetDrawlist();

    ImGuizmo::SetRect(
        mImagePos.x,
        mImagePos.y,
        mSize.x,
        mSize.y
    );

    // Obtener el objeto seleccionado
    uint32_t objectId = mContext.getSelectedObjectId();
    Object* objectSelected = mScene.findObject(objectId);

    if (objectSelected != nullptr) {
        Transform& transform = objectSelected->getTransform();

        // Obtención de matrices necesarias para Manipulate()
        glm::mat4 modelMatrix = transform.getModelMatrix();

        glm::mat4 viewMatrix = mCamera.getViewMatrix();

        glm::mat4 perspectiveMatrix = mCamera.getPerspectiveMatrix(getAspectRatio());

        //enum ImGuizmo::OPERATION operation;
        std::optional<ImGuizmo::OPERATION> operation;

        editor::Tool toolSelected = mContext.getTool();
        switch (toolSelected) {
        case editor::Tool::Move:
            operation = ImGuizmo::TRANSLATE;
            break;
        case editor::Tool::Rotate:
            operation = ImGuizmo::ROTATE;
            break;
        case editor::Tool::Scale:
            operation = ImGuizmo::SCALE;
            break;
        default:
            break;
        }

        editor::TransformMode modeSelected = mContext.getTransformMode();
        enum ImGuizmo::MODE mode;
        switch (modeSelected) {
        case editor::TransformMode::World:
            mode = ImGuizmo::WORLD;
            break;

        default:
            mode = ImGuizmo::LOCAL;
            break;
        }

        if (operation) {
            ImGuizmo::Manipulate(
                glm::value_ptr(viewMatrix),
                glm::value_ptr(perspectiveMatrix),
                *operation,
                mode,
                glm::value_ptr(modelMatrix)
            );
        }

        // Recomponer de model a position,rotation y scale
        if (ImGuizmo::IsUsing()) {
            transform.setFromModelMatrix(modelMatrix);
        }
    }
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
