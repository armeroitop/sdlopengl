
#include "mesh.hpp"
#include "app.hpp"

#include <iostream>
#include <glm/gtx/rotate_vector.hpp>


Mesh::Mesh( float uOffset, float uRotation, float uScale)
    :  m_uOffset(uOffset), m_uRotation(uRotation), m_uScale(uScale) {
}
Mesh::~Mesh() {
    // Destructor por defecto
}

void Mesh::setVertexData(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
    mVertexPosition = vertices;
    mIndices = indices;
}

void Mesh::initialize() {

    if (mVertexPosition.empty()) {
        std::cerr << "Error: No se han establecido los datos de vértices para el mesh." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (mIndices.empty()) {
        std::cerr << "Error: No se han establecido los datos de índices para el mesh." << std::endl;
        exit(EXIT_FAILURE);
    }

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Buffer para los vértices
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        mVertexPosition.size() * sizeof(GLfloat),
        mVertexPosition.data(),
        GL_STATIC_DRAW
    );

    // Buffer para los índices de triangulos
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        mIndices.size() * sizeof(GLuint),
        mIndices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // aquí el 1 es el location del atributo aColor

    // Desvincular VAO y VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::update(float deltatime) {
    // Actualización de la lógica del mesh (si es necesario)
    model = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(0.0f, 0.0f, m_uOffset)
    );

    model = glm::rotate(
        model,
        glm::radians(m_uRotation * 10.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    model = glm::scale(
        model,
        glm::vec3(m_uScale, m_uScale, m_uScale)
    );
}


void Mesh::draw() {
    // Lógica de dibujo del mesh

    glBindVertexArray(mVAO);
    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(mIndices.size()),
        GL_UNSIGNED_INT,
        0
    );
}

void Mesh::cleanup() {
    // Limpieza de recursos (si es necesario)
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

const glm::mat4& Mesh::getModelMatrix() const {
    return model;
}
