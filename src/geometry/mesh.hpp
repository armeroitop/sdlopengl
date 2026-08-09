#pragma once

#include <vector>

#include "vertex.hpp"

namespace app::geometry {
    
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;


    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

};

} // namespace app::geometry