#pragma once

#include <string>

#include "geometry/mesh.hpp"
#include "render/gl_mesh.hpp"
#include "math/transform.hpp"


class Object {

private:
    app::geometry::Mesh mesh;
    GLMesh glmesh;
    uint32_t mId;
    std::string mName;

public:
    Transform transform;

    Object(uint32_t id,
        const std::string& name,
        const app::geometry::Mesh& mesh,
        const Transform& transform
    );
    ~Object();

    void update(float dt);
    void draw() const;
    glm::mat4 getModelMatrix() const;
    uint32_t getId() const;
    std::string getName() const;
};



