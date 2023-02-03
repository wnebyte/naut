#include <iostream>
#include "core/window.h"
#include "core/camera.h"
#include "core/orthocamera.h"
#include "core/perspectivecamera.h"

using namespace core;
#define NEWL "\n"

void print(const OrthoCamera& camera) {
    glm::vec3 eye = camera.getViewEye();
    std::cout << "x=" << eye.x << ", y=" << eye.y << ", z=" << eye.z << NEWL;
}

int main() {
    PerspectiveCamera* camera;
    return 0;
}
