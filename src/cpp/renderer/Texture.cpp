#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "renderer/texture.h"

#define RGB 3
#define RGBA 4

namespace renderer {

    typedef unsigned char byte;

    Texture::Parameter::Parameter(int name, int value) noexcept
    : name(name), value(value)
    {}

    Texture::Parameter::Parameter(const Parameter& rhs) noexcept
    : Parameter(rhs.name, rhs.value)
    {}

    Texture::Parameter::Parameter(Parameter&& rhs) noexcept
    : name(std::move_if_noexcept(rhs.name)), value(std::move_if_noexcept(rhs.value))
    {}

    Texture::Parameter& Texture::Parameter::operator=(const Parameter& rhs) noexcept
    {
        if (this == &rhs) return *this;
        name = rhs.name;
        value = rhs.value;
        return *this;
    }

    Texture::Parameter& Texture::Parameter::operator=(Parameter&& rhs) noexcept
    {
        name = std::move_if_noexcept(rhs.name);
        value = std::move_if_noexcept(rhs.value);
        return *this;
    }

    Texture::Texture(const std::string& path, int target, int level, int internalFormat, int width, int height,
                     int format, int type, const std::initializer_list<Parameter>& params)
                     : id(0), path(path), target(target), level(level), internalFormat(internalFormat),
                       width(width), height(height), format(format), type(type), params(params) {
        init();
    }

    // Note: does not depend on {internalFormat, width, height, format, type}
    void Texture::init()
    {
        // Generate texture on GPU
        glGenTextures(1, &id);
        glBindTexture(target, id);

        // Set the texture parameters
        for (auto it = params.cbegin(); it != params.cend(); ++it) {
            glTexParameteri(target, it->name, it->value);
        }

        int channels;
        stbi_set_flip_vertically_on_load(true);
        byte* image = stbi_load(path.c_str(), &width, &height, &channels, 0);
        stbi_set_flip_vertically_on_load(false);

        if (image != NULL) {
            if (channels == RGB) {
                glTexImage2D(target, level, GL_RGB, width, height,
                             0, GL_RGB, GL_UNSIGNED_BYTE, (const void*)image);
            } else if (channels == RGBA) {
                glTexImage2D(target, level, GL_RGBA, width, height,
                             0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)image);
            } else {
                std::cerr << "Error: (Texture) Unknown number of channels '" << channels << "'." << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Error: (Texture) Could not load image '" << path << "'." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        stbi_image_free(image);
    }

    void Texture::resize(int newWidth, int newHeight)
    {
        width = newWidth;
        height = newHeight;
        init();
    }

    void Texture::bind()
    {
        glBindTexture(target, id);
    }

    void Texture::unbind()
    {
        glBindTexture(target, 0);
    }

    int Texture::getId() const noexcept
    {
        return id;
    }

    std::string Texture::getPath() const noexcept
    {
        return path;
    }

    int Texture::getTarget() const noexcept
    {
        return target;
    }

    int Texture::getLevel() const noexcept
    {
        return level;
    }

    int Texture::getInternalFormat() const noexcept
    {
        return internalFormat;
    }

    int Texture::getWidth() const noexcept
    {
        return width;
    }

    int Texture::getHeight() const noexcept
    {
        return height;
    }

    int Texture::getFormat() const noexcept
    {
        return format;
    }

    int Texture::getType() const noexcept
    {
        return type;
    }
}
