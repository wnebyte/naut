#ifndef NAUT_MESH_H
#define NAUT_MESH_H

#include <vector>
#include "primitives.h"
#include "texturefwd.h"
#include "shaderfwd.h"

typedef uint32_t uint;

namespace renderer {
    class Mesh {
    public:
        std::vector<Vertex3> vertices;
        std::vector<uint> indices;
        std::vector<Texture> textures;

        Mesh(const std::vector<Vertex3>& vertices,
             const std::vector<uint>& indices,
             const std::vector<Texture>& textures);

        void render(const Shader& shader);

    private:
        uint vao;
        uint vbo;
        uint ebo;

        void init();
    };
}

#endif //NAUT_MESH_H
