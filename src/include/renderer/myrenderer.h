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
        MyRenderer(Camera*);

        ~MyRenderer() noexcept = default;

        void render() override;

        void drawTriangle2(const std::array<Vertex2, 3>& vertices);

        void drawVertex2(const Vertex2&);

        void drawLine2(const Line2& line);

    private:
        Camera* camera;
        std::vector<BatchRenderer<gl_Line2>> line2Batches;
        std::vector<BatchRenderer<Vertex2>> vertex2Batches;
        std::vector<Renderer*> batches;
    };
}

#endif //NAUT_MYRENDERER_H
