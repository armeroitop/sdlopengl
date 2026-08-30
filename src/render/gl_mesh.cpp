#include "gl_mesh.hpp"

#include <iostream>

using  app::geometry::Mesh;
using  app::geometry::Vertex;

GLenum GLMesh::getOpenGLPrimitiveType() const {

    switch (mMesh.mPrimitiveType) {
        case app::geometry::PrimitiveType::Points:
            return GL_POINT;
        case app::geometry::PrimitiveType::Lines:
            return GL_LINES;
        case app::geometry::PrimitiveType::LineStrip:
            return GL_LINE_STRIP;
        case app::geometry::PrimitiveType::Triangles:
            return GL_TRIANGLES;
    }

    return GL_TRIANGLES;
}

GLMesh::GLMesh(const Mesh& mesh) : mMesh(mesh) {
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
        mesh.vertices.size() * sizeof(Vertex),
        mesh.vertices.data(),
        GL_STATIC_DRAW
    );

    // Buffer para los índices de triangulos
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        mesh.indices.size() * sizeof(mesh.indices[0]),
        mesh.indices.data(),
        GL_STATIC_DRAW
    );

    // Atributo Position - aPos del Shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0); // aquí el 0 es el location del atributo aPos

    // Atributo Color - aColor del Shader
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
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
        getOpenGLPrimitiveType(),
        indexCount,
        GL_UNSIGNED_INT,
        0
    );
}
