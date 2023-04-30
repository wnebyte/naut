#ifndef NAUT_TEXTURE_H
#define NAUT_TEXTURE_H

#include <string>
#include <vector>
#include <initializer_list>
#include "texturefwd.h"

namespace renderer {
    class Texture {
    public:
        struct Parameter {
            int32_t name;
            int32_t value;

            Parameter(int32_t name, int32_t value) noexcept;

            ~Parameter() noexcept = default;

            Parameter(const Parameter& rhs) noexcept = default;

            Parameter& operator=(const Parameter& rhs) noexcept = default;

            Parameter(Parameter&& rhs) noexcept = default;

            Parameter& operator=(Parameter&& rhs) noexcept = default;
        };

        Texture(const std::string& path,
                uint32_t target,
                const std::initializer_list<Parameter>& params = {});

        Texture(uint32_t target,
                int32_t internalFormat,
                int32_t width,
                int32_t height,
                uint32_t format,
                uint32_t type,
                const std::initializer_list<Parameter>& params = {});

        ~Texture() noexcept = default;

        void resize(int32_t, int32_t);

        void bind() const;

        void unbind() const;

        uint32_t getId() const noexcept;

        std::string getPath() const noexcept;

        uint32_t getTarget() const noexcept;

        int32_t getWidth() const noexcept;

        int32_t getHeight() const noexcept;

        operator uint32_t() const noexcept;

    private:
        uint32_t id;
        std::string path;
        uint32_t target;
        int32_t internalFormat;
        int32_t width;
        int32_t height;
        uint32_t format;
        uint32_t type;
        std::vector<Parameter> params;
    };
}

#endif //NAUT_TEXTURE_H
