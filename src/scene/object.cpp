#include "object.hpp"

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
}

Object::~Object() {
}

void Object::update(float dt) {
    mTransform.rotation.y += dt * 10.0f;
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
