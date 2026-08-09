#include "vertex.hpp"

namespace app::geometry {

Vertex::Vertex(const glm::vec3& pos)
    : position(pos) {
}

Vertex::Vertex(const glm::vec3& pos, const glm::vec3& col)
    :position(pos), color(col) {

}

} // namespace app::geometry
