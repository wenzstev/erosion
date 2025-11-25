cmake_minimum_required(VERSION 4.0)

project(erosion)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

include(FetchContent)
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/libigl/libigl-glad
        GIT_TAG master
)
FetchContent_MakeAvailable(glad)
add_library(glad_loader
    ${glad_SOURCE_DIR}/src/glad.c
)
target_include_directories(glad_loader
    PUBLIC ${glad_SOURCE_DIR}/include
)

add_library(stb_image INTERFACE)
target_include_directories(
        stb_image
        INTERFACE
        ${stb_SOURCE_DIR}
)

add_library(terrain_lib
    HeightmapGenerator.cpp
    HeightmapGenerator.h
    Mesh.h
    Vertex.h
    stb_image_impl.cpp
        Window.h
        Window.cpp
        Shader.h
        Shader.cpp
        Renderer.cpp
        Renderer.h

)

target_include_directories(terrain_lib
        PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(terrain_lib
    PUBLIC
    glm::glm
        glad
        glfw
        PRIVATE stb_image
)

add_executable(erosion
   main.cpp
)

target_link_libraries(erosion
        PRIVATE
        terrain_lib
)

enable_testing()
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)
add_subdirectory(test)