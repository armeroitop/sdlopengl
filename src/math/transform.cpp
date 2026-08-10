#include "transform.hpp"
#include <cmath>


glm::mat4 Transform::getModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);

    // Traslación
    model = glm::translate(model, position);

    // Rotación quaternaria
    model *= glm::mat4_cast(rotation);

    // Escalado
    model = glm::scale(model, scale);

    return model;
}

void Transform::setFromModelMatrix(const glm::mat4& model) {
     // Traslación
    position = glm::vec3(model[3]);

    // Escala
    scale.x = glm::length(glm::vec3(model[0]));
    scale.y = glm::length(glm::vec3(model[1]));
    scale.z = glm::length(glm::vec3(model[2]));

    // Matriz de rotación normalizada
    glm::mat3 rotationMatrix;

    rotationMatrix[0] = glm::vec3(model[0]) / scale.x;
    rotationMatrix[1] = glm::vec3(model[1]) / scale.y;
    rotationMatrix[2] = glm::vec3(model[2]) / scale.z;

    // Rotación directo desde Quaternion
    rotation = glm::quat_cast(rotationMatrix);
}

glm::vec3 Transform::getRotationEuler() const {
    //return glm::degrees(glm::eulerAngles(rotation));

    
    glm::mat3 matrix = glm::mat3_cast(rotation);

    float sy = glm::clamp(
        matrix[2][0],
        -1.0f,
        1.0f
    );

    float x;
    float y;
    float z;

    constexpr float epsilon = 0.00001f;

    if (1.0f - std::abs(sy) < epsilon) {

        // Gimbal lock
        z = 0.0f;

        if (sy > 0.0f) {

            // Y = +90°
            y = glm::half_pi<float>();

            x = std::atan2(
                matrix[0][1],
                matrix[1][1]
            );

        } else {

            // Y = -90°
            y = -glm::half_pi<float>();

            x = -std::atan2(
                matrix[0][1],
                matrix[1][1]
            );
        }

    } else {

        // Caso normal
        y = std::asin(sy);

        x = std::atan2(
            -matrix[2][1],
            matrix[2][2]
        );

        z = std::atan2(
            -matrix[1][0],
            matrix[0][0]
        );
    }

    return glm::degrees(glm::vec3(x, y, z));
}

void Transform::setRotationEuler(const glm::vec3& euler) {

    glm::quat quatX = glm::angleAxis(
        glm::radians(euler.x),
        glm::vec3{ 1.0f, 0.0f, 0.0f }
    );

    glm::quat quatY = glm::angleAxis(
        glm::radians(euler.y),
        glm::vec3{ 0.0f, 1.0f, 0.0f }
    );

    glm::quat quatZ = glm::angleAxis(
        glm::radians(euler.z),
        glm::vec3{ 0.0f, 0.0f, 1.0f }
    );

    rotation = quatX * quatY * quatZ; 

    //rotation = glm::quat(glm::radians(euler));
}
