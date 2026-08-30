#include "geometry/mesh.hpp"

namespace app::geometry {

Mesh::Mesh(const std::vector<Vertex>& vertices,
    const std::vector<uint32_t>& indices,
    const PrimitiveType primitiveType)
    :vertices(vertices),
    indices(indices),
    mPrimitiveType(primitiveType) {
}

} // namespace app::geometry