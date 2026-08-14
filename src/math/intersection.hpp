#pragma once

#include "aabb.hpp"
#include "ray.hpp"

namespace math
{
    bool intersect (
        const Ray& ray,
        const AABB& box,
        float& distance
    );
} // namespace math

