#include "geometry/mesh.hpp"

namespace app::geometry {

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
    :vertices(vertices), indices(indices) 
{
}

} // namespace app::geometry