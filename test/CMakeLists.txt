cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(runTests
    test_heightmap_generator.cpp
)

target_link_libraries(runTests
    PRIVATE
        terrain_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)