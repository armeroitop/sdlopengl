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
    mTransform(transform)
    {
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

/* const math::AABB Object::calculateBoundingBox(const Mesh& mesh) const {

    if (mesh.vertices.empty()) {
        return math::AABB{
           glm::vec3(0.0f),
           glm::vec3(0.0f)
        };
    }

    glm::vec3 min = mesh.vertices[0].position;
    glm::vec3 max = mesh.vertices[0].position;

    for (const app::geometry::Vertex& vertex : mesh.vertices) {
        min = glm::min(min, vertex.position);
        max = glm::max(max, vertex.position);
    }
    return math::AABB{ min, max };
} */

