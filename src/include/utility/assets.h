#ifndef NAUT_ASSETS_H
#define NAUT_ASSETS_H

#include <string>
#include <map>
#include "renderer/shaderfwd.h"
#include "renderer/texturefwd.h"

using namespace renderer;

namespace utility {
    class Assets {
    public:
        static const Shader& getShader(const std::string& vertexPath, const std::string& fragmentPath);

        static const Texture& getTexture(const std::string& path);

        static void free();

    private:
        static std::map<std::string, std::shared_ptr<Shader>> shaders;
        static std::map<std::string, std::shared_ptr<Texture>> textures;
    };
}

#endif //NAUT_ASSETS_H
