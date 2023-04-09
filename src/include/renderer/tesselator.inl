#ifndef NAUT_TESSELATOR_INL
#define NAUT_TESSELATOR_INL

#include "tesselator.h"
#include "primitives.h"

namespace renderer {

    template<typename T>
    void Tesselator<T>::tesselate(const T &, std::size_t, T *) {}

    template<>
    void Tesselator<Vertex2>::tesselate(const Vertex2 &, std::size_t, Vertex2*) {

    }
}

#endif //NAUT_TESSELATOR_INL
