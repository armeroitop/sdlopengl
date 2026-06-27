#pragma once
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "core/mesh.hpp"

class GLMesh
{
private:
    GLuint VAO, VBO, EBO;
    GLsizei indexCount;

public:
    GLMesh(const Mesh& mesh);
    ~GLMesh();

    void draw() const;
};


