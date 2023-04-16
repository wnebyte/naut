#ifndef NAUT_MYRENDERER_H
#define NAUT_MYRENDERER_H

#include <vector>
#include <array>
#include "renderer.h"
#include "batchrenderer.h"
#include "primitives.h"

namespace renderer {
    class MyRenderer : public Renderer {
    public:
        MyRenderer(std::shared_ptr<Camera> camera);

        ~MyRenderer() noexcept = default;

        void render() override;

        void drawTriangle2(std::array<Vertex2, 3>& vertices);

        void drawVertex2(Vertex2&);

        void drawLine2(const Line2& line);

    private:
        std::shared_ptr<Camera> camera;
        std::vector<BatchRenderer<gl_Line2>> l2_batches;
        std::vector<BatchRenderer<Vertex2>> v2_batches;
        std::vector<Renderer*> batches;
    };
}

#endif //NAUT_MYRENDERER_H
