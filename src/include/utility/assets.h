#ifndef NAUT_ASSETS_H
#define NAUT_ASSETS_H

#include <string>
#include "renderer/shaderfwd.h"
#include "renderer/texturefwd.h"

using namespace renderer;

namespace utility {
    namespace assets {
        Shader& getShader(const std::string&, const std::string&);

        Texture& getTexture(const std::string&);
    }
}

#endif //NAUT_ASSETS_H
