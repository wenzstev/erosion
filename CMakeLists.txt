cmake_minimum_required(VERSION 4.0)

project(erosion)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)

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
        glad::glad
        glfw
        PRIVATE stb_image
)

add_executable(erosion
        main.cpp
        Application.cpp
        Application.h
        AppConfig.h
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
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)
add_subdirectory(test)
