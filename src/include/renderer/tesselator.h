#ifndef NAUT_TESSELATOR_H
#define NAUT_TESSELATOR_H

namespace renderer {
    template<typename T>
    class Tesselator {
    public:
        Tesselator() = default;

        virtual ~Tesselator() noexcept = default;

    };
}

#endif //NAUT_TESSELATOR_H
