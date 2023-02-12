#include <memory>
#include <glad/glad.h>
#include "renderer/box.h"

#define SIZE 36
#define SCALE glm::vec3{1.0f, 1.0f, 1.0f}

namespace renderer {

    static const glm::vec3 VEC3S[8] = {
            glm::vec3{-0.5f,0.5f, 0.5f},
            glm::vec3{0.5f, 0.5f, 0.5f},
            glm::vec3{-0.5f,-0.5f,0.5f},
            glm::vec3{0.5f, -0.5f,0.5f},
            glm::vec3{-0.5f,0.5f, -0.5f},
            glm::vec3{0.5f, 0.5f, -0.5f},
            glm::vec3{-0.5f,-0.5f,-0.5f},
            glm::vec3{0.5f, -0.5f,-0.5f},
    };

    static const unsigned int INDICES[36] = {
            1,   0,  2, 3,  1,  2,
            5,   1,  3, 7, 5, 3,
            7, 6, 4, 5, 7, 4,
            0, 4, 6, 2, 0, 6,
            5, 4, 0, 1, 5, 0,
            3, 2, 6, 7, 3, 6
    };

    static glm::vec3* getDistinctPositions(const glm::vec3& position, const glm::vec3& scale)
    {
        static const uint sz = 8;
        glm::vec3* vertices = new glm::vec3[sz];

        for (uint i = 0; i < sz; ++i) {
            glm::vec3 v = VEC3S[i];
            glm::vec3 pos{position.x + (v.x * scale.x),
                          position.y + (v.y * scale.y),
                          position.z + (v.z * scale.z)};
            vertices[i] = pos;
        }

        return vertices;
    }

    std::initializer_list<VertexAttribute> Box::Tesselator::Attrs() {
        static std::initializer_list<VertexAttribute> attr{
                VertexAttribute{0, 3, GL_FLOAT, sizeof(Type), (void*)0},
                VertexAttribute{1, 4, GL_FLOAT, sizeof(Type), (void*)offsetof(Type, color)}
        };
        return attr;
    }

    std::size_t Box::Tesselator::Size() {
        return SIZE;
    }

    void Box::Tesselator::tesselate(const Box& box, std::size_t position_t, Type* data) const {
        std::unique_ptr<glm::vec3[]> ptr{getDistinctPositions(box.position, SCALE)};
        uint offset = position_t * SIZE;

        for (uint i = 0; i < 36; ++i) {
            uint index = INDICES[i];
            data[offset++] = Type{ptr[index], box.color};
        }
    }
}
