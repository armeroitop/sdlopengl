#pragma once
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace render {

class Shader {
private:
    GLuint mProgram = 0;

    std::unordered_map<std::string, GLint> mUniforms;

    std::string loadSource(const std::string& filename);

    GLuint compile(GLenum type, const std::string& source);

    bool link(GLuint vertexShader, GLuint fragmentShader);

public:
    Shader(/* args */);
    ~Shader();

    bool load(const std::string& vertexFile, const std::string& fragmentFile);

    void use() const;

    void setMat4(const std::string& name, const glm::mat4& value);

    GLint getUniformLocation(const std::string& name);
};

} // namespace render
