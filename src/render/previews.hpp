#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>


namespace render {
class Previews {
public:
    Previews();
    ~Previews();

    bool init();

    void drawLine(
        const glm::vec3& pointA,
        const glm::vec3& pointB
    );

    void shutdown();

private:

    GLuint mVAO = 0;
    GLuint mVBO = 0;
};
} // namespace render

