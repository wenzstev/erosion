cmake_minimum_required(VERSION 4.0)

project(erosion)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

option(ENABLE_CLANG_TIDY "Enable clang-tidy analysis" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

include(FetchContent)

find_package(glm CONFIG QUIET)
if(NOT glm_FOUND)
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glm)
endif()

find_package(glfw3 CONFIG QUIET)
if (NOT glfw3_FOUND)
    FetchContent_Declare(
            glfw3
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG 3.4
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glfw3)
endif ()

find_package(glad CONFIG QUIET)
if (NOT glad_FOUND)
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/libigl/libigl-glad
            GIT_TAG master
            GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(glad)
endif ()

find_package(Stb QUIET)
if (NOT Stb_FOUND)
    FetchContent_Declare(
            Stb
            GIT_REPOSITORY https://github.com/nothings/stb.git
            GIT_TAG master
            GIT_SHALLOW true
    )
    FetchContent_MakeAvailable(Stb)
endif()

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

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)
add_subdirectory(test)
