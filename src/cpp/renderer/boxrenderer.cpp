#if 0
#include <memory>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include "core/camera.h"
#include "renderer/boxrenderer.h"
#include "renderer/shader.h"

#define MAX_BATCH_SIZE 400

namespace renderer {

    using core::Camera;

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

    BoxRenderer::BoxRenderer()
        : vao(0), vbo(0), sz(0), initialized(false), data(new Vertex[MAX_BATCH_SIZE * 36]) {}

    BoxRenderer::~BoxRenderer() noexcept
    {
        try {
            delete[] data;
        } catch ( ... ) {}
    }

    void BoxRenderer::init()
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * 36 * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        initialized = true;
    }

    void BoxRenderer::render(const Camera* const camera, const Shader& shader)
    {
        if (sz <= 0) {
            return;
        }
        if (!initialized) {
            init();
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sz * 36 * sizeof(Vertex), (void*)data);

        shader.use();
        shader.uploadMat4(U_VIEW, camera->getViewMatrix());
        shader.uploadMat4(U_PROJECTION, camera->getProjectionMatrix());

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, sz * 36);
        glBindVertexArray(0);
        sz = 0;
        shader.detach();
    }

    bool BoxRenderer::add(const Box& box)
    {
        if (sz < MAX_BATCH_SIZE) {
            tesselate(box);
            ++sz;
            return true;
        } else {
            return false;
        }
    }

    void BoxRenderer::tesselate(const Box& box)
    {
        std::unique_ptr<glm::vec3[]> ptr{getDistinctPositions(box.position, glm::vec3{1.0f, 1.0f, 1.0f})};
        uint offset = sz * 36;

        for (uint i = 0; i < 36; ++i) {
            uint index = INDICES[i];
            glm::vec3 pos = ptr[index];
            data[offset++] = Vertex{pos, box.color};
        }
    }

    std::size_t BoxRenderer::size() const noexcept
    {
        return sz;
    }
}
#endif
