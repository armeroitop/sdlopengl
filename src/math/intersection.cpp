#include "intersection.hpp"

#include <limits>

bool math::intersect(const Ray& ray, const AABB& box, float& distance) {

    //p(x) = o + t.d

    //Para un eje X
    // o.x = ray.origen.x
    // d = ray.direction.x
    // p = box.min o box.max

    // calular intervalo t1 y t2
    // t = (p - o) / d

    float tMin = -std::numeric_limits<float>::infinity(); // -infinito
    float tMax = std::numeric_limits<float>::infinity();  // +infinito

    // Para vista en perspectiva y rayos no paralelos a ejes
    if (ray.direction.x != 0) {

        float tx_min = (box.min.x - ray.origin.x) / ray.direction.x;
        float tx_max = (box.max.x - ray.origin.x) / ray.direction.x;

        if (tx_min > tx_max) {
            std::swap(tx_min, tx_max);
        }

        // Recortamos el segmento de coincidencia
        tMin = std::max(tMin, tx_min);
        tMax = std::min(tMax, tx_max);

        if (tMin > tMax) {
            return false;
        }

    } else {
        if (ray.origin.x < box.min.x ||
            ray.origin.x > box.max.x) {
            return false;
        }
    }

    if (ray.direction.y != 0) {

        float ty_min = (box.min.y - ray.origin.y) / ray.direction.y;
        float ty_max = (box.max.y - ray.origin.y) / ray.direction.y;

        if (ty_min > ty_max) {
            std::swap(ty_min, ty_max);
        }

        // Recortamos el segmento de coincidencia
        tMin = std::max(tMin, ty_min);
        tMax = std::min(tMax, ty_max);

        if (tMin > tMax) {
            return false;
        }

    } else {

        if (ray.origin.y < box.min.y ||
            ray.origin.y > box.max.y) {
            return false;
        }
    }

    if (ray.direction.z != 0) {

        float tz_min = (box.min.z - ray.origin.z) / ray.direction.z;
        float tz_max = (box.max.z - ray.origin.z) / ray.direction.z;

        if (tz_min > tz_max) {
            std::swap(tz_min, tz_max);

        }

        tMin = std::max(tMin, tz_min);
        tMax = std::min(tMax, tz_max);

        if (tMin > tMax) {
            return false;
        }

    } else {

        if (ray.origin.z < box.min.z ||
            ray.origin.z > box.max.z) {
            return false;
        }
    }

    // Evitamos la selección detrás de la cámara
    if (tMax < 0.0f) {
        return false;
    }

    distance = std::max(tMin, 0.0f);

    return true;
}