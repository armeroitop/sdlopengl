#include "previews.hpp"

namespace render {


Previews::Previews() {
}

Previews::~Previews() {
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

bool Previews::init() {
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(glm::vec3) * 2,
        nullptr,
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec3),
        nullptr
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

void Previews::drawLine(
    const glm::vec3& pointA,
    const glm::vec3& pointB
) {
    const glm::vec3 vertices [] = {
        pointA,
        pointB
    };

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glBindVertexArray(mVAO);

    glDrawArrays(GL_LINES, 0, 2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Previews::shutdown() {

    if (mVBO != 0) {
        glDeleteBuffers(1, &mVBO);
        mVBO = 0;
    }

    if (mVAO != 0) {
        glDeleteVertexArrays(1, &mVAO);
        mVAO = 0;
    }
}

} // namespace render

