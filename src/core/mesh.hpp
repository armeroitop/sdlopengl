#pragma once


#include <glad/glad.h>
#include <vector>

struct Mesh {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;


    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);

};
