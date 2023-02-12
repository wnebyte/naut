#ifndef NAUT_BATCHRENDERER_H
#define NAUT_BATCHRENDERER_H

#include <initializer_list>
#include "core/camerafwd.h"
#include "shaderfwd.h"
#include "vertexattribute.h"
#include "utility/types.h"
#include "renderer.h"

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
        uint vao;
        uint vbo;
        typename T::Tesselator::Type* data;
        std::size_t sz;
        bool initialized;
    };
}

#include "batchrendererimpl.inl"

#endif //NAUT_BATCHRENDERER_H
