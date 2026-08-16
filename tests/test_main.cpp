#include <iostream>
#include "test.hpp"


int main() {
    bool success = true;

    success &= testBoundingBox();
    success &= testRayHitsAABBFromOutside();
    success &= testRayMissesAABB();
    success &= testRayStartsInsideAABB();
    success &= testRayParallelOutsideAABB();

   return success ? EXIT_SUCCESS : EXIT_FAILURE;
}