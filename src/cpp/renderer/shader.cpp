#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "renderer/shader.h"

namespace renderer {

    static const GLsizei sz = 1024;

    static void checkCompileErrors(GLuint shader, const std::string& type) {
        GLint success;
        GLchar infoLog[sz];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, sz, NULL, infoLog);
            std::cerr << "Error: (Shader) Compilation error for shader: " << type << "\n" << infoLog <<
                      "\n-- --------------------------------------------------- --" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    static void checkLinkErrors(GLuint shader) {
        GLint success;
        GLchar infoLog[sz];
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, sz, NULL, infoLog);
            std::cerr << "Error: (Shader) Link error\n" << infoLog <<
                      "\n-- --------------------------------------------------- --" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    static std::string readifstream(const std::string& path) {
        std::string src;
        std::ifstream ifs;
        ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            ifs.open(path, std::ios::in);
            std::stringstream ss;
            ss << ifs.rdbuf();
            ifs.close();
            src = ss.str();
        } catch (std::ifstream::failure &e) {
            std::cerr << "Error: (Shader) Could not open file for '" << path << "'\nwhat: " << e.what() << std::endl;
            throw e;
        }

        return src;
    }

    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
            : id(0), vertexPath(vertexPath), fragmentPath(fragmentPath),
              vertexSrc(readifstream(vertexPath)), fragmentSrc(readifstream(fragmentPath)),
              detached(true) {}

    void Shader::compile() {
        uint32_t vertexID;
        uint32_t fragmentID;
        const char *cVertexSrc = vertexSrc.c_str();
        const char *cFragmentSrc = fragmentSrc.c_str();

        // Load and compile the vertex shader
        vertexID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexID, 1, &cVertexSrc, NULL);
        glCompileShader(vertexID);
        checkCompileErrors(vertexID, "VERTEX");

        // Load and compile the fragment shader
        fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentID, 1, &cFragmentSrc, NULL);
        glCompileShader(fragmentID);
        checkCompileErrors(fragmentID, "FRAGMENT");

        // Link shaders
        id = glCreateProgram();
        glAttachShader(id, vertexID);
        glAttachShader(id, fragmentID);
        glLinkProgram(id);
        checkLinkErrors(id);

        // Delete the shaders
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);
    }

    void Shader::use() const {
        if (detached) {
            glUseProgram(id);
            detached = false;
        }
    }

    void Shader::detach() const {
        glUseProgram(0);
        detached = true;
    }

    uint32_t Shader::getId() const noexcept {
        return id;
    }

    std::string Shader::getVertexPath() const noexcept {
        return vertexPath;
    }

    std::string Shader::getFragmentPath() const noexcept {
        return fragmentPath;
    }

    std::string Shader::getVertexSrc() const noexcept {
        return vertexSrc;
    }

    std::string Shader::getFragmentSrc() const noexcept {
        return fragmentSrc;
    }

    void Shader::uploadInt(const std::string &varName, int i) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform1i(varLocation, i);
    }

    void Shader::uploadFloat(const std::string &varName, float f) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform1f(varLocation, f);
    }

    void Shader::uploadIntArray(const std::string &varName, const int *array) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform1iv(varLocation, 1, array);
    }

    void Shader::uploadFloatArray(const std::string &varName, const float *array) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform1fv(varLocation, 1, array);
    }

    void Shader::uploadVec2(const std::string &varName, const glm::vec2 &vec) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform2fv(varLocation, 1, &vec[0]);
    }

    void Shader::uploadVec3(const std::string &varName, const glm::vec3 &vec) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform3fv(varLocation, 1, &vec[0]);
    }

    void Shader::uploadVec4(const std::string &varName, const glm::vec4 &vec) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform4fv(varLocation, 1, &vec[0]);
    }

    void Shader::uploadMat3(const std::string &varName, const glm::mat3 &mat) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniformMatrix3fv(varLocation, 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::uploadMat4(const std::string &varName, const glm::mat4 &mat) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniformMatrix4fv(varLocation, 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::uploadTexture(const std::string &varName, int slot) const {
        use();
        int varLocation = glGetUniformLocation(id, varName.c_str());
        glUniform1i(varLocation, slot);
    }
}
