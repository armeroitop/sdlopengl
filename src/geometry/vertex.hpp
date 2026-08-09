#pragma once
#include <glm/glm.hpp>

namespace app::geometry {

struct Vertex {
    glm::vec3 position;
    glm::vec3 color{ 1.0f, 1.0f, 1.0f };

    Vertex() = default;

    Vertex(const glm::vec3& pos);

    Vertex(const glm::vec3& pos, const glm::vec3& col);
};

} // namespace geometry
