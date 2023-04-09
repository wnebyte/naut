#ifndef NAUT_VERTEXATTRIBUTE_H
#define NAUT_VERTEXATTRIBUTE_H

#include "defs.h"

namespace renderer {
    struct VertexAttribute {
        int size;
        uint type;
        int stride;
        void* offset;
    };
}

#endif //NAUT_VERTEXATTRIBUTE_H
