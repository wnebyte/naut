#ifndef NAUT_BATCHRENDERER_H
#define NAUT_BATCHRENDERER_H

#include <memory>
#include <initializer_list>
#include "core/camerafwd.h"
#include "shaderfwd.h"
#include "renderer.h"
#include "vertexattribute.h"
#include "defs.h"

#define N_TEXTURES (16u)

namespace renderer {

    using namespace core;

    template<typename T>
    class BatchRenderer : public Renderer {
    public:
        BatchRenderer(std::shared_ptr<Camera>, std::shared_ptr<Shader> shader, uint32_t mode = GL_TRIANGLES);

        ~BatchRenderer() noexcept;

        void init(const std::initializer_list<VertexAttribute>&);

        void render() override;

        bool add(const T&);

        std::size_t size() const noexcept;

    private:
        uint32_t vao;
        uint32_t vbo;
        uint32_t mode;
        T* data;
        std::size_t n;
        std::array<int32_t, N_TEXTURES> textures;
        bool initialized;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Shader> shader;
    };
}

#include "batchrenderer.inl"

#endif //NAUT_BATCHRENDERER_H
