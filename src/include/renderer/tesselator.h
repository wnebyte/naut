#ifndef NAUT_TESSELATOR_H
#define NAUT_TESSELATOR_H

#include <cstddef>

namespace renderer {

    template<typename T>
    class Tesselator {
    public:
        Tesselator() = default;

        ~Tesselator() noexcept = default;

        void tesselate(const T&, std::size_t, T*);
    };
}

#include "tesselator.inl"

#endif //NAUT_TESSELATOR_H
