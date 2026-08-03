#include "shader.hpp"

#include <iostream>
#include <fstream>

namespace render {

std::string Shader::loadSource(const std::string& filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (!file) {
        throw std::runtime_error("No se pudo abrir el archivo shader.");
    }

    return std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}

GLuint Shader::compile(GLenum type, const std::string& source) {

    GLuint shader = glCreateShader(type);

    // 1. Extraemos el puntero a la cadena estilo C (const char*)
    const GLchar* src = source.c_str();

    // 2. Pasamos la dirección de 'src' (&src) a OpenGL
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // 3. Comprobación
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "Error compilando "
            << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
            << " shader:\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool Shader::link(GLuint vertexShader, GLuint fragmentShader) {

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);

    GLint linked;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);
    if (!linked) {
        char infoLog[1024];
        glGetProgramInfoLog(mProgram, 1024, nullptr, infoLog);
        std::cerr << "Error enlazando programa:\n" << infoLog << std::endl;
        glDeleteProgram(mProgram);
        mProgram = 0;
        return false;
    }
    return true;
}


Shader::Shader() {
}

Shader::~Shader() {
    if (mProgram != 0) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}

bool render::Shader::load(const std::string& vertexFile, const std::string& fragmentFile) {

    std::string vertexSource = loadSource(vertexFile);
    std::string fragmentSource = loadSource(fragmentFile);

    GLuint vertexShader = compile(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compile(GL_FRAGMENT_SHADER, fragmentSource);

    if (!vertexShader || !fragmentShader) {
        return false;
    }

    bool success = link(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return success;
}

void Shader::use() const {
    //printf("Shader program = %u\n", mProgram);
    glUseProgram(mProgram);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) {
    GLint location = getUniformLocation(name);

    if (location == -1) {
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

GLint Shader::getUniformLocation(const std::string& name) {
    auto it = mUniforms.find(name);
    if (it != mUniforms.end()) {
        // La clave existe y podemos acceder a su valor con it->second
        return it->second;
    }

    GLint location = glGetUniformLocation(mProgram, name.c_str());

    if (location == -1) {
        std::cerr
            << "Uniform no encontrado: "
            << name
            << std::endl;
    }

    mUniforms[name] = location;

    return location;
}

} // namespace render

