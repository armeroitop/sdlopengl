#pragma once
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "geometry/mesh.hpp"

class GLMesh
{
private:
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;
    const app::geometry::Mesh& mMesh;

    GLenum getOpenGLPrimitiveType() const;

public:
    GLMesh(const app::geometry::Mesh& mesh);
    ~GLMesh();

    void draw() const;
};


