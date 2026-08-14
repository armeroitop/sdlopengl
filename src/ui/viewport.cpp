#include "viewport.hpp"
#include "math/intersection.hpp"


#include <glm/gtc/type_ptr.hpp>
#include <optional>
#include <iostream>


namespace ui {

glm::vec2 Viewport::screenToNDC(const glm::vec2& mouseAbsolutePosition) const {

    glm::vec2 mousePositionViewport{
        mouseAbsolutePosition.x - mImagePos.x,
        mouseAbsolutePosition.y - mImagePos.y
    };

    return glm::vec2{
        mousePositionViewport.x / mSize.x * 2 - 1,
        -mousePositionViewport.y / mSize.y * 2 + 1
    };
}

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

void Viewport::update(const input::Input& input) {
    if (!input.leftMouseDown ||
        !isMouseOver(input.mouseAbsolutePosition)) {
        return;
    }
    // hemos hecho click dentro del viewport

    math::Ray worldRay =
        screenToRay(input.mouseAbsolutePosition);

    std::cout
        << "worldRay origin: "
        << worldRay.origin.x << ", "
        << worldRay.origin.y << ", "
        << worldRay.origin.z
        << '\n';

    std::cout
        << "worldRay direction: "
        << worldRay.direction.x << ", "
        << worldRay.direction.y << ", "
        << worldRay.direction.z
        << '\n';

    float closestDistance =
        std::numeric_limits<float>::infinity();

    const Object* selectedObject = nullptr;
    for (const Object& object : mScene.getObjects()) {

        glm::mat4 modelMatrix =
            object.getTransform().getModelMatrix();

        math::Ray localRay =
            worldToLocalRay(worldRay, modelMatrix);

        float localDistance;

        if (math::intersect(
            localRay,
            object.getBoundingBox(),
            localDistance)) {


            glm::vec3 localHitPoint =
                localRay.origin +
                localDistance * localRay.direction;

            glm::vec3 worldHitPoint =
                glm::vec3(modelMatrix * glm::vec4(localHitPoint, 1.0f));

            float worldDistance =
                glm::length(worldHitPoint - worldRay.origin);

            std::cout
                << "Hit object: "
                << object.getName()
                << " | world_distance = "
                << worldDistance
                << " | local_distance = "
                << localDistance
                << '\n';

            if (worldDistance < closestDistance) {
                closestDistance = worldDistance;
                mContext.setSelectedObjectId(object.getId());
            }
        }

    }

    if (selectedObject != nullptr) {

        mContext.setSelectedObjectId(
            selectedObject->getId()
        );
    }

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

bool Viewport::isMouseOver(const glm::ivec2& mouseAbsolutePosition) const {

    float left = mImagePos.x;
    float right = mImagePos.x + mSize.x;
    float top = mImagePos.y;
    float bottom = mImagePos.y + mSize.y;

    return (
        mouseAbsolutePosition.x >= left
        && mouseAbsolutePosition.x <= right
        && mouseAbsolutePosition.y <= bottom
        && mouseAbsolutePosition.y >= top
        );
}

math::Ray Viewport::screenToRay(const glm::vec2& mouseAbsolutePosition) const {

    glm::vec2 ndc = screenToNDC(mouseAbsolutePosition);

    //Crear dos vec4 near y far;
    glm::vec4 nearPointNDC{ ndc.x, ndc.y, -1.0f, 1.0f };
    glm::vec4 farPointNDC{ ndc.x, ndc.y, 1.0f, 1.0f };

    //Matriz de inversión, de NDC a World
    glm::mat4 inverseViewProjection = glm::inverse(
        mCamera.getPerspectiveMatrix(getAspectRatio()) * mCamera.getViewMatrix());

    // Transformar near y far a world
    glm::vec4 nearPointWorld = inverseViewProjection * nearPointNDC;
    glm::vec4 farPointWorld = inverseViewProjection * farPointNDC;

    // Realizar la división perspectiva
    glm::vec3 nearPoint = glm::vec3(nearPointWorld / nearPointWorld.w);
    glm::vec3 farPoint = glm::vec3(farPointWorld / farPointWorld.w);

    // Construir el rayo

    math::Ray ray;

    ray.origin = nearPoint;
    ray.direction = glm::normalize(farPoint - nearPoint);

    return ray;

}

math::Ray Viewport::worldToLocalRay(const math::Ray& worldRay, const glm::mat4& modelMatrix) const {

    glm::mat4 inverseModel = glm::inverse(modelMatrix);

    glm::vec4 origin = inverseModel * glm::vec4(worldRay.origin, 1.0f);

    glm::vec4 direction = inverseModel * glm::vec4(worldRay.direction, 0.0f);

    math::Ray localRay;

    localRay.origin = glm::vec3(origin);
    localRay.direction = glm::normalize(glm::vec3(direction));

    return localRay;
}

} // namespace ui
