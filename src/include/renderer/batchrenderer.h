#ifndef NAUT_BATCHRENDERER_H
#define NAUT_BATCHRENDERER_H

#include <initializer_list>
#include "core/camerafwd.h"
#include "shaderfwd.h"
#include "renderer.h"
#include "vertexattribute.h"
#include "defs.h"

namespace renderer {

    using namespace core;

    template<typename T>
    class BatchRenderer : public Renderer {
    public:
        BatchRenderer(const std::initializer_list<VertexAttribute>&, Camera*, Shader*);

        ~BatchRenderer() noexcept;

        void init();

        void render() override;

        bool add(const T&);

        std::size_t size() const noexcept;

    private:
        uint32_t vao;
        uint32_t vbo;
        T* data;
        std::size_t sz;
        bool initialized;
        int32_t zIndex;
        std::vector<VertexAttribute> attrs;
        Camera* camera;
        Shader* shader;
    };
}

#include "batchrenderer.inl"

#endif //NAUT_BATCHRENDERER_H
