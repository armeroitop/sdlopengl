#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "math/transform.hpp"
class Camera {
private:
    // Transform
    glm::vec3 mPosition;
    glm::vec3 mViewDirection;
    glm::vec3 mUpVector;

    // Orbit
    glm::vec3 mPivot{ 0.0f };

    // Orientation
    float mYaw = -90.0f;
    float mPitch = 0.0f;
    float mSensitivity = 0.1f;

    // Projection
    float mFov = 45.0f;
    float mNearPlane = 0.1f;
    float mFarPlane = 100.0f;

    // Movement
    float mSpeed = 0.0f;

    void rotateAround(
        glm::vec3& movinPoint,
        const glm::vec3& fixedPoint,
        float xrel,
        float yrel
    );


public:
    Camera(/* args */);
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveMatrix(float aspect) const;

    glm::vec3 getForward() const;
    glm::vec3 getForwardNormalized() const;

    void setPivot(const glm::vec3& position);
    const glm::vec3& getPivot() const;
    void focus(const glm::vec3& position, const float radius);

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void translate(const glm::vec3& delta);

    void mouseLook(float xrel, float yrel);
    void orbit(float xrel, float yrel);
    void zoom(float amount);
    void zoomAtPoint(float amount, const glm::vec3& zoomPoint);
    void pan(float dx, float dy);
};