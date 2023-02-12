#ifndef NAUT_VERTEXATTRIBUTE_H
#define NAUT_VERTEXATTRIBUTE_H

#include "utility/types.h"

namespace renderer {
    struct VertexAttribute {
        uint index;
        int size;
        uint type;
        int stride;
        void* offset;
    };
}

#endif //NAUT_VERTEXATTRIBUTE_H
