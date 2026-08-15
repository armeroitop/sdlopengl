#include <iostream>
#include <cmath>
#include <cassert>

#include "math/intersection.hpp"

bool testRayHitsAABB() {

    math::AABB box{
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f)
    };

    math::Ray ray{
        glm::vec3(-5.0f, 0.0f, 0.0f),
        glm::vec3( 1.0f, 0.0f, 0.0f)
    };

    float distance = 0.0f;

    bool hit = math::intersect(
        ray,
        box,
        distance
    );

    if (!hit) {
        std::cerr
            << "[FAIL] Rayo atraviesa AABB: "
            << "se esperaba una intersección\n";

        return false;
    }

    if (std::abs(distance - 4.0f) >= 0.0001f) {
        std::cerr
            << "[FAIL] Rayo atraviesa AABB: "
            << "distancia incorrecta\n";

        std::cerr
            << "  Esperado: 4.0\n"
            << "  Obtenido: " << distance << '\n';

        return false;
    }

    std::cout << "[PASS] Rayo atraviesa AABB\n";

    return true;
}