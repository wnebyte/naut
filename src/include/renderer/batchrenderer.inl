#ifndef NAUT_BATCHRENDERER_INL
#define NAUT_BATCHRENDERER_INL

#include <glad/glad.h>
#include "batchrenderer.h"
#include "core/camera.h"
#include "shader.h"
#include "vertexattribute.h"
#include "primitives.h"

#define MAX_BATCH_SIZE 400

namespace renderer {

    template<typename T>
    BatchRenderer<T>::BatchRenderer()
    : vao(0), vbo(0), sz(0), initialized(false), zIndex(0), tesselator(Tesselator{}),
      data(new typename T::Tesselator::Type[MAX_BATCH_SIZE * T::Tesselator::size()]) {}

    template<typename T>
    BatchRenderer<T>::~BatchRenderer() noexcept {
        try {
            glDeleteBuffers(1, &vbo);
            glDeleteVertexArrays(1, &vao);
            delete[] data;
        } catch ( ... ) {}
    }

    template<typename T>
    void BatchRenderer<T>::init() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * T::Tesselator::size() * sizeof(typename T::Tesselator::Type), NULL, GL_DYNAMIC_DRAW);

        uint32_t i = 0;
        for (auto& attr : T::Tesselator::attrs()) {
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
    void BatchRenderer<T>::render(const Camera& camera, const Shader& shader) {
        if (sz == 0) {
            return;
        }
        if (!initialized) {
            init();
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sz * Tesselator::size() * sizeof(typename Tesselator::Type), (void*)data);

        shader.use();
        shader.uploadMat4(U_VIEW, camera.getViewMatrix());
        shader.uploadMat4(U_PROJECTION, camera.getProjectionMatrix());

        glBindVertexArray(vao);
        /*
         * mode - Specifies what kind of primitives to render.
         * Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY,
         * GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY,
         * GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.
         * first - Specifies the starting index in the enabled arrays.
         * count -  Specifies the number of indices to be rendered.
         */
        glDrawArrays(GL_TRIANGLES, 0, sz * Tesselator::size() * sizeof(typename Tesselator::Type));
        glBindVertexArray(0);
        sz = 0;
        shader.detach();
    }

    template<typename T>
    bool BatchRenderer<T>::add(const T& t) {
        if (sz < MAX_BATCH_SIZE) {
            tesselator.tesselate(t, sz, data);
            ++sz;
            return true;
        } else {
            return false;
        }
    }

    template<typename T>
    std::size_t BatchRenderer<T>::size() const noexcept {
        return sz;
    }
}

#endif //NAUT_BATCHRENDERER_INL
