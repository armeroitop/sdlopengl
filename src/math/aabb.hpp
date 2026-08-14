#pragma once
#include <glm/glm.hpp>
// AABB significa Axis-Aligned Bounding Box, es decir:
// Caja delimitadora alineada con los ejes.

namespace math {

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

} // namespace math
