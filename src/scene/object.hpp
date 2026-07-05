#pragma once

#include "geometry/mesh.hpp"
#include "render/gl_mesh.hpp"
#include "math/transform.hpp"


class Object {

private:
app::geometry::Mesh mesh;
GLMesh glmesh;

public:
    Transform transform;

    Object(const app::geometry:: Mesh& mesh, const Transform& transform);
    ~Object();

    void update(float dt);
    void draw() const;
    glm::mat4 getModelMatrix() const;
};



