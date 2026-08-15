#include "aabb.hpp"
#include "geometry/mesh.hpp"

namespace math {


AABB calculateBoundingBox(const app::geometry::Mesh& mesh) {

    if (mesh.vertices.empty()) {
        return AABB{
           glm::vec3(0.0f),
           glm::vec3(0.0f)
        };
    }

    glm::vec3 min = mesh.vertices[0].position;
    glm::vec3 max = mesh.vertices[0].position;

    for (const app::geometry::Vertex& vertex : mesh.vertices) {
        min = glm::min(min, vertex.position);
        max = glm::max(max, vertex.position);
    }
    return AABB{ min, max };
}

} // namespace math