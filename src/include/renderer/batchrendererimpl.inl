#ifndef NAUT_BATCHRENDERERIMPL_INL
#define NAUT_BATCHRENDERERIMPL_INL

#include "batchrenderer.h"
#include "core/camera.h"
#include "shader.h"
#include "vertexattribute.h"

#define MAX_BATCH_SIZE 400

namespace renderer {

    template<typename T>
    BatchRenderer<T>::BatchRenderer()
    : vao(0), vbo(0), initialized(false), sz(0),
      data(new typename T::Tesselator::Type[MAX_BATCH_SIZE * T::Tesselator::Size()]) {}

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
        glBufferData(GL_ARRAY_BUFFER, MAX_BATCH_SIZE * T::Tesselator::Size() * sizeof(typename T::Tesselator::Type), NULL, GL_DYNAMIC_DRAW);

        for (auto& attr : T::Tesselator::Attrs()) {
            if (attr.type == GL_FLOAT) {
                glVertexAttribPointer(attr.index, attr.size, GL_FLOAT, false, attr.stride, attr.offset);
            } else {
                glVertexAttribIPointer(attr.index, attr.size, attr.type, attr.stride, attr.offset);
            }
            glEnableVertexAttribArray(attr.index);
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
        glBufferSubData(GL_ARRAY_BUFFER, 0, sz * T::Tesselator::Size() * sizeof(typename T::Tesselator::Type), (void*)data);

        shader.use();
        shader.uploadMat4(U_VIEW, camera.getViewMatrix());
        shader.uploadMat4(U_PROJECTION, camera.getProjectionMatrix());

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, sz * T::Tesselator::Size());
        glBindVertexArray(0);
        sz = 0;
        shader.detach();
    }

    template<typename T>
    bool BatchRenderer<T>::add(const T& t) {
        if (sz < MAX_BATCH_SIZE) {
            typename T::Tesselator tesselator{};
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

#endif //NAUT_BATCHRENDERERIMPL_INL
