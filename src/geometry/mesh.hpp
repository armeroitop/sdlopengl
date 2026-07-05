#pragma once


#include <glad/glad.h>
#include <vector>

namespace app::geometry {
    
struct Mesh {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;


    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);

};

} // namespace app::geometry