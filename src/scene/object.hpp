#pragma once

#include <string>

#include "geometry/mesh.hpp"
#include "render/gl_mesh.hpp"
#include "math/transform.hpp"


class Object {

private:
    app::geometry::Mesh mMesh;
    GLMesh mGLmesh;
    uint32_t mId;
    std::string mName;
    Transform mTransform;

public:

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

    Transform& getTransform();
    const Transform& getTransform() const;
};



