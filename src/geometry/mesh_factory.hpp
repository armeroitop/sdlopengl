#pragma once

#include "mesh.hpp"


namespace app::geometry {
class MeshFactory {
private:
    /* data */
public:
    MeshFactory(/* args */);
    ~MeshFactory();

    static Mesh createRectangleMesh();
    static Mesh createCubeMesh();

    static Mesh createLine(const glm::vec3& pointA, const glm::vec3& pointB);
};

} // namespace app_geometry
