#ifndef NAUT_BATCHRENDERER_H
#define NAUT_BATCHRENDERER_H

#include <initializer_list>
#include "core/camerafwd.h"
#include "shaderfwd.h"
#include "renderer.h"
#include "defs.h"

namespace renderer {

    using namespace core;

    template<typename T>
    class BatchRenderer : public Renderer {
    public:
        BatchRenderer();

        ~BatchRenderer() noexcept;

        void init();

        void render(const Camera&, const Shader&) override;

        bool add(const T&);

        std::size_t size() const noexcept;

    private:
        typedef typename T::Tesselator Tesselator;
        uint32_t vao;
        uint32_t vbo;
        Tesselator tesselator;
        typename Tesselator::Type* data;
        std::size_t sz;
        bool initialized;
        int32_t zIndex;
    };
}

#include "batchrenderer.inl"

#endif //NAUT_BATCHRENDERER_H
