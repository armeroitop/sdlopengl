#include "camera.hpp"
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>



glm::vec3 Camera::getForward() const {
    return glm::normalize(mPivot - mPosition);
}

glm::vec3 Camera::getForwardNormaliced() const {
    glm::vec3 forward = getForward();
    forward.y = 0.0f;
    return glm::normalize(forward);
}

Camera::Camera(/* args */) {
    mPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    //mViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    mPivot = glm::vec3(0.0f, 0.0f, 2.0f);
    mUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
    mSpeed = 0.5f;
    mYaw = -90.0f;
    mPitch = 0.0f;
    mSensitivity = 0.1f;
}

Camera::~Camera() {
}


glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(
        mPosition,
        //mPosition + mViewDirection,
        mPivot,
        mUpVector
    );
}

glm::mat4 Camera::getPerspectiveMatrix(float aspect) const {

    return glm::perspective(
        glm::radians(mFov),
        aspect,
        mNearPlane,
        mFarPlane
    );
}

void Camera::moveForward(float deltaTime) {
    float velocity = mSpeed * deltaTime;

    glm::vec3 forwardNormaliced = getForwardNormaliced();

    translate(forwardNormaliced * velocity);
}

void Camera::moveBackward(float deltaTime) {
    float velocity = mSpeed * deltaTime;

    glm::vec3 forwardNormaliced = getForwardNormaliced();

    translate(-forwardNormaliced * velocity);
}

void Camera::moveLeft(float deltaTime) {
    float velocity = mSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(getForward(), mUpVector));
    translate(-right * velocity);
}

void Camera::moveRight(float deltaTime) {
    float velocity = mSpeed * deltaTime;

    glm::vec3 right = glm::normalize(glm::cross(getForward(), mUpVector));

    translate(right * velocity);
}

void Camera::translate(const glm::vec3& delta) {
    mPosition += delta;
    mPivot += delta;
}

void Camera::mouseLook(float xrel, float yrel) {
    // Parameters are treated as relative mouse movement (deltas)
    float deltaY = yrel;
    float deltaX = xrel;

    //std::cout << "Mouse delta:(" << deltaX << ", " << deltaY << ")\n";

    // update yaw and pitch (invert Y if needed)
    mYaw += deltaX * mSensitivity;
    mPitch -= deltaY * mSensitivity;

    // clamp pitch to avoid flipping
    if (mPitch > 89.0f) mPitch = 89.0f;
    if (mPitch < -89.0f) mPitch = -89.0f;

    // calculate new front vector from yaw and pitch
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mViewDirection = glm::normalize(front);
}

void Camera::zoom(float amount) {
    // TODO: cambiar a 
    // direction = normalize(mPivot - mPosition)
    translate(amount * getForward());
}

void Camera::pan(float dx, float dy) {
    const glm::vec3 right = glm::normalize(glm::cross(getForward(), mUpVector));

    const glm::vec3 displacement =
        right * (-dx) +
        mUpVector * dy;

    constexpr float panSpeed = 0.01f;

    translate(displacement * panSpeed);
}

