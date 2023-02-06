#include <glad/glad.h>
#include <string>
#include "renderer/mesh.h"
#include "renderer/texture.h"
#include "renderer/shader.h"

namespace renderer {

    Mesh::Mesh(const std::vector<Vertex3D>& vertices,
               const std::vector<uint>& indices,
               const std::vector<Texture>& textures)
               : vertices(vertices), indices(indices), textures(textures)
    {
        init();
    }

    void Mesh::init()
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), &vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, uv));
        glEnableVertexAttribArray(2);
    }

    void Mesh::draw(const Shader& shader)
    {
        uint diffuseNr = 1;
        uint specularNr = 1;
        uint i = 0;
        for (auto it = textures.begin(); it != textures.end(); ++it, ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, it->getId());
            std::string number;
            std::string name = it->getPath(); // tmp
            if (name == "diffuse")
                number = std::to_string(i);
            else if (name == "specular")
                number = std::to_string(i);

            shader.uploadInt(("material." + name + number), i);
        }

        // draw mesh
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(0);
    }
}
