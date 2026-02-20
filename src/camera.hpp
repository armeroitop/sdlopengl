#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 mEye;
    glm::vec3 mViewDirection;
    glm::vec3 mUpVector;
    glm::vec2 mLastMousePosition;

    glm::mat4 mViewMatrix;

    float mSpeed = 0.0f;
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    // mouse control state
    float mYaw = -90.0f;
    float mPitch = 0.0f;
    float mSensitivity = 0.1f;
    bool mFirstMouse = true;


public:
    Camera(/* args */);
    ~Camera();

    glm::mat4 getViewMatrix() const;

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRighit(float deltaTime);

    void mouseLook(float mouseX, float mouseY);




};