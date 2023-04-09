#include <glad/glad.h>
#include <algorithm>
#include <memory>
#include "utility/assets.h"
#include "renderer/shader.h"
#include "renderer/texture.h"

namespace utility {

    typedef std::map<std::string, std::shared_ptr<Shader>>  Shaders;
    typedef std::map<std::string, std::shared_ptr<Texture>> Textures;

    void Assets::free() {
        try {
            for (Shaders::iterator it = shaders.begin(); it != shaders.end(); ++it) {
                Shader *shader = it->second.get();
                delete shader;
            }
            for (Textures::iterator it = textures.begin(); it != textures.end(); ++it) {
                Texture *texture = it->second.get();
                delete texture;
            }
            shaders.clear();
            textures.clear();
        } catch ( ... ) {}
    }

    const Shader& Assets::getShader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string path = vertexPath + fragmentPath;
        Shaders::iterator it = shaders.find(path);

        if (it != shaders.end()) {
            // shader has been loaded
            return *(it->second.get());
        } else {
            // shader has not yet been loaded
            std::shared_ptr<Shader> shader{new Shader{vertexPath, fragmentPath}};
            shaders[path] = shader;
            return *(shader.get());
        }
    }

    const Texture& Assets::getTexture(const std::string& path) {
        Textures::iterator it = textures.find(path);

        if (it != textures.end()) {
            // texture has been loaded
            return *(it->second.get());
        } else {
            // texture has not yet been loaded
            std::shared_ptr<Texture> texture{new Texture{path, GL_TEXTURE_2D}};
            textures[path] = texture;
            return *(texture.get());
        }
    }
}
