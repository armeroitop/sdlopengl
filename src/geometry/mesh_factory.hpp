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
};

} // namespace app_geometry
