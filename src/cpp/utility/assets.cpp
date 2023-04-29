#include <map>
#include <assert.h>
#include <glad/glad.h>
#include "utility/assets.h"
#include "renderer/shader.h"
#include "renderer/texture.h"

namespace utility {

    namespace assets {

        static std::map<std::string, Texture> textures{};
        static std::map<std::pair<std::string, std::string>, Shader> shaders{};

        Texture& getTexture(const std::string& path) {
            const auto key = path;
            const std::map<std::string, Texture>::iterator it = textures.find(key);

            if (it != textures.end()) {
                return it->second;
            } else {
                Texture texture{path, GL_TEXTURE_2D};
                auto res = textures.emplace(key, texture);
                assert(res.second == true);
                return res.first->second;
            }
        }

        Shader& getShader(const std::string& vertexPath, const std::string& fragmentPath) {
            const auto key = std::make_pair(vertexPath, fragmentPath);
            const std::map<std::pair<std::string, std::string>, Shader>::iterator it = shaders.find(key);

            if (it != shaders.end()) {
                return it->second;
            } else {
                Shader shader{vertexPath, fragmentPath};
                shader.compile();
                auto res = shaders.emplace(key, shader);
                assert(res.second == true);
                return res.first->second;
            }
        }
    }
}
