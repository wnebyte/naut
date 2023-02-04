#ifndef NAUT_SHADER_H
#define NAUT_SHADER_H

#include <string>
#include <glm/ext/matrix_float4x4.hpp>
#include "shaderfwd.h"

#define U_PROJECTION "uProjection"
#define U_VIEW "uView"

namespace renderer {
    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        ~Shader() noexcept = default;

        void compile();

        void use() const;

        void detach() const;

        unsigned int getId() const noexcept;

        std::string getVertexPath() const noexcept;

        std::string getFragmentPath() const noexcept;

        std::string getVertexSrc() const noexcept;

        std::string getFragmentSrc() const noexcept;

        void uploadInt(const std::string& varName, int i) const;

        void uploadFloat(const std::string& varName, float f) const;

        void uploadIntArray(const std::string& varName, const int array[]) const;

        void uploadFloatArray(const std::string& varName, const float array[]) const;

        void uploadVec2(const std::string& varName, const glm::vec2& vec) const;

        void uploadVec3(const std::string& varName, const glm::vec3& vec) const;

        void uploadVec4(const std::string& varName, const glm::vec4& vec) const;

        void uploadMat3(const std::string& varName, const glm::mat3& mat) const;

        void uploadMat4(const std::string& varName, const glm::mat4& mat) const;

        void uploadTexture(const std::string& varName, int slot) const;

    private:
        unsigned int id;
        std::string vertexPath;
        std::string fragmentPath;
        std::string vertexSrc;
        std::string fragmentSrc;
        mutable bool detached;
    };
}

#endif //NAUT_SHADER_H
