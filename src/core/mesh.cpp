#include "core/mesh.hpp"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
    :vertices(vertices), indices(indices) 
{
}