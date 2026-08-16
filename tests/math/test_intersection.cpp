#include <iostream>
#include <cmath>
#include <cassert>

#include "math/intersection.hpp"

/**
 * Comprueba que un rayo que parte fuera de la AABB
 * y atraviesa su volumen devuelve una intersección
 * y la distancia correcta hasta la primera cara.
 */
bool testRayHitsAABBFromOutside() {

    math::AABB box{
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f)
    };

    math::Ray ray{
        glm::vec3(-5.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
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


// El rayo no debe atravesar el cubo
bool testRayMissesAABB() {
    math::AABB box{
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f)
    };

    math::Ray ray{
        glm::vec3(-5.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };

    float distance = 0.0f;

    bool hit = math::intersect(
        ray,
        box,
        distance
    );

    if (hit) {
        std::cerr
            << "[FAIL] Rayo atraviesa AABB: "
            << "se esperaba que no atravesara el objeto\n";

        return false;
    }

    std::cout << "[PASS] Rayo no atraviesa AABB\n";

    return true;

}

// Desde dentro no debe haber intersección
bool testRayStartsInsideAABB() {
    math::AABB box{
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f)
    };

    math::Ray ray{
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };

    float distance = 0.0f;

    bool hit = math::intersect(ray, box, distance);

    if (!hit) {
        std::cerr
            << "[FAIL] Rayo comienza dentro de AABB: "
            << "se esperaba una intersección\n";

        return false;
    }

    if (std::abs(distance) >= 0.0001f) {
        std::cerr
            << "[FAIL] Rayo comienza dentro de AABB: "
            << "distancia incorrecta\n"
            << "  Esperado: 0.0\n"
            << "  Obtenido: " << distance << '\n';

        return false;
    }

    std::cout << "[PASS] Rayo comienza dentro de AABB\n";

    return true;

}

bool testRayParallelOutsideAABB() {
    math::AABB box{
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f,  1.0f,  1.0f)
    };

    math::Ray ray{
        glm::vec3(0.0f, 2.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    };

    float distance = 0.0f;

    bool hit = math::intersect(
        ray,
        box,
        distance
    );

    if (hit) {
        std::cerr
            << "[FAIL] Rayo paralelo fuera de AABB: "
            << "se esperaba que no hubiera intersección\n";

        return false;
    }

    std::cout << "[PASS] Rayo paralelo fuera de AABB\n";

    return true;
}
// bool testRayParallelInsideAABB();