cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

add_executable(runTests
        test_heightmap_generator.cpp
)

target_link_libraries(runTests
    PRIVATE
        terrain_lib
        GTest::gtest_main
)

target_compile_definitions(runTests PRIVATE TEST_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

include(GoogleTest)
gtest_discover_tests(runTests)
