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

            Parameter(const Parameter& rhs) noexcept;

            Parameter& operator=(const Parameter& rhs) noexcept;

            Parameter(Parameter&& rhs) noexcept;

            Parameter& operator=(Parameter&& rhs) noexcept;
        };

        Texture(const std::string& path,
                int target,
                int level,
                int internalFormat,
                int width,
                int height,
                int format,
                int type,
                const std::initializer_list<Parameter>& params);

        virtual ~Texture() noexcept = default;

        void resize(int, int);

        void bind();

        void unbind();

        int getId() const noexcept;

        std::string getPath() const noexcept;

        int getTarget() const noexcept;

        int getLevel() const noexcept;

        int getInternalFormat() const noexcept;

        int getWidth() const noexcept;

        int getHeight() const noexcept;

        int getFormat() const noexcept;

        int getType() const noexcept;

    private:
        unsigned int id;
        std::string path;
        int target;
        int level;
        int internalFormat;
        int width;
        int height;
        int format;
        int type;
        std::vector<Parameter> params;

        void init();
    };
}

#endif //NAUT_TEXTURE_H
