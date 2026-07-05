#include "gl_mesh.hpp"

#include <iostream>

using  app::geometry::Mesh;

GLMesh::GLMesh(const Mesh& mesh) {
    if (mesh.vertices.empty()) {
        std::cerr << "Error: No se han establecido los datos de vértices para el mesh." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (mesh.indices.empty()) {
        std::cerr << "Error: No se han establecido los datos de índices para el mesh." << std::endl;
        exit(EXIT_FAILURE);
    }

    indexCount = static_cast<GLsizei>(mesh.indices.size());
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Buffer para los vértices
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        mesh.vertices.size() * sizeof(GLfloat),
        mesh.vertices.data(),
        GL_STATIC_DRAW
    );

    // Buffer para los índices de triangulos
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        mesh.indices.size() * sizeof(GLuint),
        mesh.indices.data(),
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

GLMesh::~GLMesh() {
}

void GLMesh::draw() const {
    // Lógica de dibujo del mesh

    glBindVertexArray(VAO);
    glDrawElements(
        GL_TRIANGLES,
        indexCount,
        GL_UNSIGNED_INT,
        0
    );
}
