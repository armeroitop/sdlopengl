#pragma once
#include <glm/glm.hpp>
// AABB significa Axis-Aligned Bounding Box, es decir:
// Caja delimitadora alineada con los ejes.


namespace app::geometry { //Forward decalation de Mesh
struct Mesh;
}

namespace math {

struct AABB {
    glm::vec3 min;
    glm::vec3 max;


};

AABB calculateBoundingBox(const app::geometry::Mesh& mesh);
} // namespace math
