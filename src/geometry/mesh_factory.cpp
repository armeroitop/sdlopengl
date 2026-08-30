#include "mesh_factory.hpp"

namespace app::geometry {
MeshFactory::MeshFactory(/* args */) {
}

MeshFactory::~MeshFactory() {
}
Mesh app::geometry::MeshFactory::createRectangleMesh() {

    const std::vector<Vertex> vertexPosition{
        {{ 0.0f,  0.8f, 0.0f}, {1.0f, 0.0f, 0.0f}},  // arriba, rojo
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // izquierda, verde
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},  // derecha, azul
        {{ 1.0f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}}  // arriba, blanco
    };
    const std::vector<uint32_t> indices{
        0, 1, 2, // primer triángulo
        3, 0, 2  // segundo triángulo
    };


    return Mesh(vertexPosition, indices, PrimitiveType::Triangles);
}

Mesh app::geometry::MeshFactory::createCubeMesh() {

    const std::vector<Vertex> vertices{
        // Cara frontal (roja)
        {{-0.5f, -0.5f,  0.5f},{ 1.0f, 0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f},{ 1.0f, 0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f},{ 1.0f, 0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},{ 1.0f, 0.0f, 0.0f}},

        // Cara trasera (verde)
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}
    };

    const std::vector<uint32_t> indices{
        // Frontal
        0,1,2,
        2,3,0,

        // Derecha
        1,5,6,
        6,2,1,

        // Trasera
        5,4,7,
        7,6,5,

        // Izquierda
        4,0,3,
        3,7,4,

        // Superior
        3,2,6,
        6,7,3,

        // Inferior
        4,5,1,
        1,0,4
    };

    return Mesh(vertices, indices, PrimitiveType::Triangles);
}

Mesh MeshFactory::createLine(const glm::vec3& pointA, const glm::vec3& pointB) {
    glm::vec3 colorLine = { 1.0f,0.0f,0.0f };
    
    const std::vector<Vertex> vertices{
        {pointA, colorLine},
        {pointB, colorLine}
    };

     const std::vector<uint32_t> indices{0,1};

    return Mesh(vertices, indices, PrimitiveType::Lines);
}

} // namespace app::geometry