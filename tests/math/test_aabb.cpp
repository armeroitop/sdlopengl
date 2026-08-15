#include <iostream>
#include <cstdlib>

#include "geometry/mesh.hpp"
#include "math/aabb.hpp"
#include "scene/object.hpp"

bool testBoundingBox() {

    app::geometry::Mesh mesh(
        {
            {{-5.0f, -1.0f, -1.0f}},
            {{ 5.0f, -1.0f, -1.0f}},
            {{ 5.0f,  1.0f,  1.0f}},
            {{-5.0f,  1.0f,  1.0f}}
        },
        {}
    );

    // Aquí utilizamos nuestra función
    math::AABB box = math::calculateBoundingBox(mesh);

    glm::vec3 expectedMin{
        -5.0f, -1.0f, -1.0f
    };

    glm::vec3 expectedMax{
         5.0f,  1.0f,  1.0f
    };

    if (box.min != expectedMin) {
        std::cerr << "FAIL: BoundingBox min incorrecto\n";

        std::cerr << "Esperado: "
            << expectedMin.x << ", "
            << expectedMin.y << ", "
            << expectedMin.z << '\n';

        std::cerr << "Obtenido: "
            << box.min.x << ", "
            << box.min.y << ", "
            << box.min.z << '\n';

        return false;
    }

    if (box.max != expectedMax) {
        std::cerr << "FAIL: BoundingBox max incorrecto\n";

        std::cerr << "Esperado: "
            << expectedMax.x << ", "
            << expectedMax.y << ", "
            << expectedMax.z << '\n';

        std::cerr << "Obtenido: "
            << box.max.x << ", "
            << box.max.y << ", "
            << box.max.z << '\n';

        return false;
    }
    
    std::cout << "[PASS] BoundingBox de Mesh\n";
    return true;
}