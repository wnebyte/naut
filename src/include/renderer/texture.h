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
            int name;
            int value;

            Parameter(int name, int value) noexcept;

            ~Parameter() noexcept = default;

            Parameter(const Parameter& rhs) noexcept = default;

            Parameter& operator=(const Parameter& rhs) noexcept = default;

            Parameter(Parameter&& rhs) noexcept = default;

            Parameter& operator=(Parameter&& rhs) noexcept = default;
        };

        Texture(const std::string& path,
                uint target,
                const std::initializer_list<Parameter>& params = {});

        Texture(uint target,
                int internalFormat,
                int width,
                int height,
                uint format,
                uint type,
                const std::initializer_list<Parameter>& params = {});

        virtual ~Texture() noexcept = default;

        void resize(int, int);

        void bind() const;

        void unbind() const;

        uint getId() const noexcept;

        std::string getPath() const noexcept;

        uint getTarget() const noexcept;

        int getWidth() const noexcept;

        int getHeight() const noexcept;

    private:
        uint id;
        std::string path;
        uint target;
        int internalFormat;
        int width;
        int height;
        uint format;
        uint type;
        std::vector<Parameter> params;
    };
}

#endif //NAUT_TEXTURE_H
