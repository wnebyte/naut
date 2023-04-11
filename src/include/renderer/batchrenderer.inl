#ifndef NAUT_BATCHRENDERER_INL
#define NAUT_BATCHRENDERER_INL

#include <glad/glad.h>
#include "batchrenderer.h"
#include "core/camera.h"
#include "shader.h"
#include "vertexattribute.h"
#include "primitives.h"

#define MAX_BATCH_SIZE 400
#define NO_TEX_ID      -1

namespace renderer {

    template<typename T>
    static constexpr auto getTexId(T* obj) -> decltype( obj->texId, std::true_type{} ) {
        return obj->texId;
    }

    static constexpr auto getTexId(...) -> int32_t {
        return NO_TEX_ID;
    }


    static int32_t getTexIndex(const std::array<int32_t, N_TEXTURES>& array, const int32_t texId) {
        std::array<int32_t, N_TEXTURES>::const_iterator cit = array.begin();
        int32_t i = 0;

        do {
            if (*cit == texId) {
                return i;
            }
            ++i;
        } while (cit++ != array.end());

        return NO_TEX_ID;
    }

    template<typename T>
    BatchRenderer<T>::BatchRenderer(std::shared_ptr<Camera> camera, std::shared_ptr<Shader> shader, uint32_t mode)
    : vao(0), vbo(0), mode(mode), n(0), initialized(false), textures(), camera(camera), shader(shader),
      data(new T[MAX_BATCH_SIZE]) {
          textures.fill(NO_TEX_ID);
      }

    template<typename T>
    BatchRenderer<T>::~BatchRenderer() noexcept {
        try {
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
            delete[] data;
        } catch ( ... ) {}
    }

    template<typename T>
    void BatchRenderer<T>::init(const std::initializer_list<VertexAttribute>& attrs) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * sizeof(T), NULL, GL_DYNAMIC_DRAW);

        uint32_t i = 0;
        for (auto& attr : attrs) {
            if (attr.type == GL_FLOAT) {
                glVertexAttribPointer(i, attr.size, GL_FLOAT, false, attr.stride, attr.offset);
            } else {
                glVertexAttribIPointer(i, attr.size, attr.type, attr.stride, attr.offset);
            }
            glEnableVertexAttribArray(i);
            ++i;
        }

        initialized = true;
    }

    template<typename T>
    void BatchRenderer<T>::render() {
        if (n == 0) {
            return;
        }
        if (!initialized) {
            return;
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, n * sizeof(T), (void*)data);

        shader->use();
        shader->uploadMat4(U_VIEW, camera->getViewMatrix());
        shader->uploadMat4(U_PROJECTION, camera->getProjectionMatrix());

        glBindVertexArray(vao);
        /*
         * mode - Specifies what kind of primitives to render.
         * Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY,
         * GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY,
         * GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.
         * first - Specifies the starting index in the enabled arrays.
         * count -  Specifies the number of indices to be rendered.
         */
        glDrawArrays(mode, 0, n);
        glBindVertexArray(0);
        n = 0;
        shader->detach();
    }

    template<typename T>
    bool BatchRenderer<T>::add(const T& t) {
        if (n >= MAX_BATCH_SIZE) {
            return false;
        }
        const int32_t texId    = getTexId(t);
        const int32_t texIndex = getTexIndex(textures, texId);

        if (texId != NO_TEX_ID) {
            data[n++] = t;
            return true;
        } else if (texIndex != NO_TEX_ID) {
            textures[texIndex] = texId;
            data[n++] = t;
            return true;
        }

        return false;
    }

    template<typename T>
    std::size_t BatchRenderer<T>::size() const noexcept {
        return n;
    }
}

#endif //NAUT_BATCHRENDERER_INL
