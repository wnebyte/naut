cmake_minimum_required(VERSION 3.24)
project(Naut)

set(CMAKE_CXX_STANDARD 11)

# finds OpenGL, GLU and X11
find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message("Error: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

# sets the include directory path
set(INCLUDE_DIRECTORY src/include)

file(GLOB SOURCES CONFIGURE_DEPENDS
        "src/include/*.h"
        "src/include/*.inl"
        "src/include/core/*.h"
        "src/include/core/*.inl"
        "src/include/io/*.h"
        "src/include/io/*.inl"
        "src/include/render/*.h"
        "src/include/render/*.inl"
        "src/include/utility/*.h"
        "src/include/utility/*.inl"
        "src/c/*.c"
        "src/cpp/*.cpp"
        "src/cpp/core/*.cpp"
        "src/cpp/io/*.cpp"
        "src/cpp/renderer/*.cpp"
        "src/cpp/utility/*.cpp")

add_executable(Naut ${SOURCES})

target_link_libraries(Naut glfw3 stb ${GL_LIBRARY} m)

target_include_directories(Naut PRIVATE ${INCLUDE_DIRECTORY})

add_compile_definitions(CPP_VERSION=${CMAKE_CXX_STANDARD})
