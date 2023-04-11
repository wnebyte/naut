#include "renderer/myrenderer.h"
#include "utility/cmath.h"

namespace renderer {

    using utility::CMath;

    static const std::initializer_list<VertexAttribute> VAO_GL_LINE2 {
            VertexAttribute{2, GL_FLOAT, sizeof(gl_Line2), (void*)0},
            VertexAttribute{4, GL_FLOAT, sizeof(gl_Line2), (void*)offsetof(gl_Line2, color)}
    };

    static const std::initializer_list<VertexAttribute> VAO_GL_VERTEX2 {
            VertexAttribute{2, GL_FLOAT, sizeof(Vertex2), (void*)0},
            VertexAttribute{4, GL_FLOAT, sizeof(Vertex2), (void*)offsetof(Vertex2, color)},
            VertexAttribute{2, GL_FLOAT, sizeof(Vertex2), (void*)offsetof(Vertex2, uv)},
            VertexAttribute{1, GL_INT,   sizeof(Vertex2), (void*)offsetof(Vertex2, texId)}
    };

    template<typename T>
    static BatchRenderer<T> getBatch(int32_t zIndex, uint32_t texId, bool blendable) {
        return NULL;
    }

    MyRenderer::MyRenderer(std::shared_ptr<Camera> camera)
    : camera(camera) {}

    void MyRenderer::drawVertex2(const Vertex2& vertex) {
        bool added = false;
        for (auto& batch : vertex2Batches) {
            if (batch.add(vertex)) {
                added = true;
                break;
            }
        }
        if (!added) {
            BatchRenderer<Vertex2> batch{camera, NULL};
            batch.init(VAO_GL_VERTEX2);
            batch.add(vertex);
            vertex2Batches.push_back(batch);
            batches.push_back(&batch);
        }
    }

    void MyRenderer::drawTriangle2(const std::array<Vertex2, 3>& vertices) {
        for (auto& vertex : vertices) {
            drawVertex2(vertex);
        }
    }

    void MyRenderer::drawLine2(const Line2& line) {
        gl_Line2 lines[] = {{line.start, line.color}, {line.end, line.color} };
        uint32_t i;

        for (i = 0; i < 2; ++i) {
            gl_Line2 gl_line = lines[i];
            bool added = false;
            for (auto& batch : line2Batches) {
                if (batch.add(gl_line)) {
                    added = true;
                    break;
                }
            }
            if (!added) {
                BatchRenderer<gl_Line2> batch{camera, NULL, GL_LINES};
                batch.init(VAO_GL_LINE2);
                batch.add(gl_line);
                line2Batches.push_back(batch);
                batches.push_back(&batch);
            }
        }
    }

    void MyRenderer::render() {
        for (auto batch : batches) {
            batch->render();
        }
    }
}
