#include "geometry/mesh.hpp"

namespace app::geometry {

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    :vertices(vertices)
    , indices(indices) {
}

} // namespace app::geometry