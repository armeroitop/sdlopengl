#pragma once

#include <vector>

#include "vertex.hpp"

namespace app::geometry {

enum class PrimitiveType {
    Points,
    Lines,
    LineStrip,
    Triangles
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    PrimitiveType mPrimitiveType = PrimitiveType::Triangles;

    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<uint32_t>& indices,
         const PrimitiveType primitiveType = PrimitiveType::Triangles
        );

};

} // namespace app::geometry