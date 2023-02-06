#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "renderer/texture.h"

#define RGB 3
#define RGBA 4
#define DEFAULT_PATH "Generated"

namespace renderer {

    typedef unsigned char byte;

    static void init(GLuint* const id,
                     const std::string& path,
                     GLenum target,
                     GLsizei* const width,
                     GLsizei* const height,
                     const std::vector<Texture::Parameter>& params)
    {
        // Generate texture on GPU
        glGenTextures(1, id);
        glBindTexture(target, *id);

        // Set texture parameters
        for (auto it = params.cbegin(); it != params.cend(); ++it) {
            glTexParameteri(target, it->name, it->value);
        }

        int channels;
        byte* image = stbi_load(path.c_str(), width, height, &channels, 0);

        if (image != NULL) {
            if (channels == RGB) {
                glTexImage2D(target, 0, GL_RGB, *width, *height,
                             0, GL_RGB, GL_UNSIGNED_BYTE, (void*)image);
            } else if (channels == RGBA) {
                glTexImage2D(target, 0, GL_RGBA, *width, *height,
                             0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)image);
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

    static void init(GLuint* const id,
                     GLenum target,
                     GLint internalFormat,
                     GLsizei width,
                     GLsizei height,
                     GLenum format,
                     GLenum type,
                     const std::vector<Texture::Parameter>& params)
    {
        // Generate texture on GPU
        glGenTextures(1, id);
        glBindTexture(target, *id);

        // Set texture parameters
        for (auto it = params.cbegin(); it != params.cend(); ++it) {
            glTexParameteri(target, it->name, it->value);
        }

        glTexImage2D(target, 0, internalFormat, width, height,
                     0, format, type, NULL);
    }

    Texture::Parameter::Parameter(int name, int value) noexcept
            : name(name), value(value)
    {}

    Texture::Texture(const std::string& path, uint target, const std::initializer_list<Parameter>& params)
            : id(0), path(path), target(target), internalFormat(0),
              width(0), height(0), format(0), type(0), params(params)
    {
        init(&id, path, target, &width, &height, params);
    }

    Texture::Texture(uint target,
                     int internalFormat,
                     int width,
                     int height,
                     uint format,
                     uint type,
                     const std::initializer_list<Parameter>& params)
                     : id(0), path(DEFAULT_PATH), target(target), internalFormat(internalFormat),
                       width(width), height(height), format(format), type(type), params(params)
    {
        init(&id, target, internalFormat, width, height, format, type, params);
    }

    void Texture::resize(int newWidth, int newHeight)
    {
        if (path == DEFAULT_PATH) {
            width = newWidth;
            height = newHeight;
            init(&id, target, internalFormat, width, height, format, type, params);
        }
    }

    void Texture::bind() const
    {
        glBindTexture(target, id);
    }

    void Texture::unbind() const
    {
        glBindTexture(target, 0);
    }

    uint Texture::getId() const noexcept
    {
        return id;
    }

    std::string Texture::getPath() const noexcept
    {
        return path;
    }

    uint Texture::getTarget() const noexcept
    {
        return target;
    }

    int Texture::getWidth() const noexcept
    {
        return width;
    }

    int Texture::getHeight() const noexcept
    {
        return height;
    }

    Texture::operator uint() const noexcept
    {
        return id;
    }
}
