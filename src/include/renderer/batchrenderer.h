#ifndef NAUT_BATCHRENDERER_H
#define NAUT_BATCHRENDERER_H

#include <memory>
#include <functional>
#include <initializer_list>
#include <glad/glad.h>
#include "core/camerafwd.h"
#include "batchrendererfwd.h"
#include "shaderfwd.h"
#include "vertexattributefwd.h"
#include "renderer.h"

#define N_TEXTURES (16u)

namespace renderer {

    using namespace core;

    template<typename T>
    class BatchRenderer : public Renderer {
    public:
        BatchRenderer(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Shader>& shader, uint32_t mode = GL_TRIANGLES);

        ~BatchRenderer() noexcept;

        void init(const std::initializer_list<VertexAttribute>&);

        void render() override;

        bool add(T&);

        std::size_t size() const noexcept;

        const T& operator[](std::size_t) const;

    private:
        uint32_t vao;
        uint32_t vbo;
        uint32_t mode;
        T* data;
        std::size_t n;
        std::array<int32_t, N_TEXTURES> textures;
        std::size_t nTextures;
        bool initialized;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Shader> shader;
    };

}

#include "batchrenderer.inl"

#endif //NAUT_BATCHRENDERER_H
