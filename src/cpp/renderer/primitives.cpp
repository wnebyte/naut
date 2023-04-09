#include <glad/glad.h>
#include "renderer/primitives.h"

namespace renderer {

    std::initializer_list<VertexAttribute> Line2::Tesselator::attrs() {
        static std::initializer_list<VertexAttribute> attrs{
            VertexAttribute{2, GL_FLOAT, sizeof(Line2), (void*)0},
            VertexAttribute{4, GL_FLOAT, sizeof(Line2), (void*)offsetof(Line2, color)}
        };
        return attrs;
    }

    std::size_t Line2::Tesselator::size() {
        return 1;
    }

    void Line2::Tesselator::tesselate(const Line2& line, size_t size, Type* data) const {
        data[size] = line;
    }

    std::initializer_list<VertexAttribute> Vertex2::Tesselator::attrs() {
        static std::initializer_list<VertexAttribute> attrs{
            VertexAttribute{2, GL_FLOAT, sizeof(Vertex2), (void*)0},
            VertexAttribute{4, GL_FLOAT, sizeof(Vertex2), (void*)offsetof(Vertex2, color)},
            VertexAttribute{2, GL_FLOAT, sizeof(Vertex2), (void*)offsetof(Vertex2, uv)},
            VertexAttribute{1, GL_INT,   sizeof(Vertex2), (void*)offsetof(Vertex2, texId)}
        };
        return attrs;
    }

    std::size_t Vertex2::Tesselator::size() {
        return 1;
    }

    void Vertex2::Tesselator::tesselate(const Vertex2& vertex, size_t size, Type* data) const {
        data[size] = vertex;
    }
}
