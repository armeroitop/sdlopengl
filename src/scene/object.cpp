#include "object.hpp"

using  app::geometry::Mesh;

Object::Object(uint32_t id,
    const std::string& name,
    const Mesh& mesh,
    const Transform& transform)
    : mId(id),
    mName(name),
    mesh(mesh),
    glmesh(this->mesh),
    transform(transform) {
}

Object::~Object() {
}

void Object::update(float dt) {
    transform.rotation.y += dt * 10.0f;
}

void Object::draw() const {
    glmesh.draw();
}

glm::mat4 Object::getModelMatrix() const {
    return transform.getModelMatrix();
}

uint32_t Object::getId() const {
    return mId;
}

std::string Object::getName() const {
    return mName;
}
