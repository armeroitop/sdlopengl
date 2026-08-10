#pragma once 

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform {
    glm::vec3 position {0.0f};
    glm::quat rotation {1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 scale {1.0f};

    glm::mat4 getModelMatrix() const;
    void setFromModelMatrix(const glm::mat4& model);

    glm::vec3 getRotationEuler() const;
    void setRotationEuler(const glm::vec3& euler);
};