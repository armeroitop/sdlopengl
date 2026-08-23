#include "object.hpp"
#include <algorithm>

using  app::geometry::Mesh;

Object::Object(uint32_t id,
    const std::string& name,
    const Mesh& mesh,
    const Transform& transform)
    : mId(id),
    mName(name),
    mMesh(mesh),
    mGLmesh(this->mMesh),
    mTransform(transform) {
    mBoundingBox = math::calculateBoundingBox(mMesh);
}

Object::~Object() {
}

void Object::update(float dt) {
    //mTransform.rotation.y += dt * 10.0f;
}

void Object::draw() const {
    mGLmesh.draw();
}

glm::mat4 Object::getModelMatrix() const {
    return mTransform.getModelMatrix();
}

uint32_t Object::getId() const {
    return mId;
}

std::string Object::getName() const {
    return mName;
}

Transform& Object::getTransform() {
    return mTransform;
}

const Transform& Object::getTransform() const {
    return mTransform;
}

const math::AABB& Object::getBoundingBox() const {
    return mBoundingBox;
}

glm::vec3 Object::getWorldBoundingCenter() const {

    glm::vec3 posLocalCenter = (mBoundingBox.max + mBoundingBox.min) * 0.5f;

    glm::vec3 posWorldCenter = (
        getModelMatrix() *
        glm::vec4(posLocalCenter, 1.0f)
        );

    return posWorldCenter;
}

float Object::getWorldBoundingRadius() const {
    glm::vec3 semiDiagonal = (mBoundingBox.max - mBoundingBox.min) * 0.5f;

    float radius = glm::length(semiDiagonal);

    float maxScale = glm::max(
        mTransform.scale.x,
        glm::max(
            mTransform.scale.y,
            mTransform.scale.z
        )
    );

    return radius * maxScale;
}

