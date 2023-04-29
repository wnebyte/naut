#include "renderer/myrenderer.h"
#include "utility/math.h"

namespace renderer {

    using namespace utility::math;

    MyRenderer::MyRenderer(const std::shared_ptr<Camera>& camera)
            : camera(camera) {}

    void MyRenderer::drawVertex2(Vertex2 vertex) {
        for (auto& batch : v2_batches) {
            if (batch.add(vertex)) {
                return;
            }
        }
        BatchRenderer<Vertex2> batch{camera, NULL};
        batch.init({
            VertexAttribute{2, GL_FLOAT, sizeof(Vertex2), (void*)0},
            VertexAttribute{4, GL_FLOAT, sizeof(Vertex2), (void*)offsetof(Vertex2, color)},
            VertexAttribute{2, GL_FLOAT, sizeof(Vertex2), (void*)offsetof(Vertex2, uv)},
            VertexAttribute{1, GL_INT,   sizeof(Vertex2), (void*)offsetof(Vertex2, texId)}
        });
        batch.add(vertex);
        v2_batches.push_back(batch);
        batches.push_back(&v2_batches.back());
    }

    void MyRenderer::drawTriangle2(std::array<Vertex2, 3>& vertices) {
        for (auto& vertex : vertices) {
            drawVertex2(vertex);
        }
    }

    void MyRenderer::drawLine2(const Line2& line) {
        static constexpr std::size_t N_LINES = 2;
        gl_Line2 lines[N_LINES] = { {line.start, line.color}, {line.end, line.color} };
        uint32_t i;

        for (i = 0; i < N_LINES; ++i) {
            gl_Line2 *gl_line = &lines[i];
            bool added = false;
            for (auto& batch : l2_batches) {
                if (batch.add(*gl_line)) {
                    added = true;
                    break;
                }
            }
            if (!added) {
                BatchRenderer<gl_Line2> batch{camera, NULL, GL_LINES};
                batch.init({
                    VertexAttribute{2, GL_FLOAT, sizeof(gl_Line2), (void*)0},
                    VertexAttribute{4, GL_FLOAT, sizeof(gl_Line2), (void*)offsetof(gl_Line2, color)}
                });
                batch.add(*gl_line);
                l2_batches.push_back(batch);
                batches.push_back(&l2_batches.back());
            }
        }
    }

    void MyRenderer::render() {
        for (auto batch : batches) {
            batch->render();
        }
    }
}
