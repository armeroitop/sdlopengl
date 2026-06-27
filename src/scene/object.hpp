#pragma once

#include "core/mesh.hpp"
#include "graphics/gl_mesh.hpp"
#include "math/transform.hpp"


class Object {

private:
Mesh mesh;
GLMesh glmesh;

public:
    Transform transform;

    Object(const Mesh& mesh, const Transform& transform);
    ~Object();

    void update(float dt);
    void draw() const;
    glm::mat4 getModelMatrix() const;
};



