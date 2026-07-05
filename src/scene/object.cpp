#include "object.hpp"

using  app::geometry::Mesh;

Object::Object(const Mesh& mesh, const Transform& transform) 
    : mesh(mesh),glmesh(this->mesh),transform(transform)
{
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