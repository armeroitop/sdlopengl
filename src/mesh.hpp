#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Forward declaration de App para evitar dependencias circulares
struct App;

struct Mesh {
    App* app = nullptr;

    std::vector<GLfloat> mVertexPosition;
    std::vector<GLuint> mIndices;

    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;

    GLint mModelLoc;
    GLint mPerspectiveLoc;
    GLint mViewLoc;

    float m_uOffset = -2.0f;
    float m_uRotation = 0.0f;
    float m_uScale = 1.0f;

    glm::mat4 model;
    glm::mat4 perspective;
    glm::mat4 view;

    Mesh(App* app, float uOffset, float uRotation, float uScale);
    ~Mesh();
    void setVertexData(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) ;
    void initialize();
    void update(float deltatime);
    void setUniforms();
    void draw();
    void cleanup();
};

