#ifndef NAUT_VERTEXATTRIBUTE_H
#define NAUT_VERTEXATTRIBUTE_H

#include "vertexattributefwd.h"

namespace renderer {
    struct VertexAttribute {
        int32_t size;
        uint32_t type;
        int32_t stride;
        void* offset;
    };
}

#endif //NAUT_VERTEXATTRIBUTE_H
