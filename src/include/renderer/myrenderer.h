#ifndef NAUT_MYRENDERER_H
#define NAUT_MYRENDERER_H

#include <vector>
#include "renderer.h"
#include "batchrenderer.h"

namespace renderer {
    class MyRenderer : public Renderer {
    public:
        MyRenderer() = default;

        ~MyRenderer() noexcept = default;

        void render(const Camera&, const Shader&) override;

        void drawVertex2(const Vertex2&);

        void drawLine2(const glm::vec2&, const glm::vec2&, const glm::vec4&);

    private:
        std::vector<BatchRenderer<Line2>> line2Batches;
        std::vector<BatchRenderer<Vertex2>> vertex2Batches;
        std::vector<Renderer*> batches;
    };
}

#endif //NAUT_MYRENDERER_H
