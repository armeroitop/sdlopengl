#include <iostream>

bool testBoundingBox();
bool testRayHitsAABB();

int main() {
    bool success = true;

    success &= testBoundingBox();
    success &= testRayHitsAABB();

   return success ? EXIT_SUCCESS : EXIT_FAILURE;
}