#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    // Transform
    glm::vec3 mEye;
    glm::vec3 mViewDirection;
    glm::vec3 mUpVector;
    
    // Orbit
    glm::vec3 mPivot{0.0f};

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
    

public:
    Camera(/* args */);
    ~Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveMatrix(float aspect) const;

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void mouseLook(float mouseX, float mouseY);
    void zoom(float amount);
    void pan(float dx, float dy);
};