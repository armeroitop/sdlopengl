#include "grid.hpp"

namespace render {

Grid::Grid() {
}

bool Grid::init() {
    constexpr int size = 20;

    for (int i = 0; i < size; i++) {

        glm::vec3 verticeXC1{ i,0,size };
        glm::vec3 verticeXC3{ i,0,-size };
        glm::vec3 verticeXC2{ -i,0,size };
        glm::vec3 verticeXC4{ -i,0,-size };

        mVertices.push_back(verticeXC1);
        mVertices.push_back(verticeXC3);
        mVertices.push_back(verticeXC2);
        mVertices.push_back(verticeXC4);

        glm::vec3 verticeYC1{ size,0,i };
        glm::vec3 verticeYC3{ -size,0,i };
        glm::vec3 verticeYC2{ size,0,-i };
        glm::vec3 verticeYC4{ -size,0,-i };

        mVertices.push_back(verticeYC1);
        mVertices.push_back(verticeYC3);
        mVertices.push_back(verticeYC2);
        mVertices.push_back(verticeYC4);
    }
    mVertexCount = mVertices.size();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Buffer para los vértices
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        mVertexCount * sizeof(glm::vec3),
        mVertices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    // Desvincular VAO y VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}
void Grid::draw() {

    glBindVertexArray(mVAO);
    glDrawArrays(
        GL_LINES,
        0,
        mVertexCount
    );
    glBindVertexArray(0);
}
} // namespace render

