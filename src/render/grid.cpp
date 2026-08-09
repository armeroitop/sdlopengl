#include "grid.hpp"

namespace render {

Grid::Grid() {
}

bool Grid::init() {
    constexpr int size = 20;
    glm::vec3 colorX;
    glm::vec3 colorZ;

    for (int i = 0; i < size; i++) {
        if (i == 0) {
            colorX = { 1.0f,0.0f,0.0f };
            colorZ = { 0.0f,0.0f,1.0f };
        } else {
            colorX = { 0.0f,0.0f,0.0f };
            colorZ = { 0.0f,0.0f,0.0f };
        }
        
        //Paralelas a Eje Z
        mVertices.emplace_back(glm::vec3{ i,0,size }, colorZ);
        mVertices.emplace_back(glm::vec3{ i,0,-size }, colorZ);
        mVertices.emplace_back(glm::vec3{ -i,0,size }, colorZ);
        mVertices.emplace_back(glm::vec3{ -i,0,-size }, colorZ);

        //Paralelas a Eje X
        mVertices.emplace_back(glm::vec3{ size,0,i },colorX);
        mVertices.emplace_back(glm::vec3{ -size,0,i },colorX);
        mVertices.emplace_back(glm::vec3{ size,0,-i },colorX);
        mVertices.emplace_back(glm::vec3{ -size,0,-i },colorX);
    }
    mVertexCount = mVertices.size();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Buffer para los vértices
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        mVertexCount * sizeof(Vertex),
        mVertices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // Atributo Color - aColor del Shader
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1); // aquí el 1 es el location del atributo aColor

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

