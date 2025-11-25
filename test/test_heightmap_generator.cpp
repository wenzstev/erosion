/*
 * =====================================================================================
 * test_heightmap_generator.cpp
 *
 * Unit tests for the HeightmapGenerator class.
 * =====================================================================================
 */

#include "gtest/gtest.h"
#include "HeightmapGenerator.h" // The class we are testing
#include "Mesh.h"
#include "glm/glm.hpp"

// --- Test Case 1: File Not Found ---
// Test that the generator handles a non-existent file gracefully.
TEST(HeightmapGeneratorTest, HandlesFileNotFound) {
    // Act: Try to load a file that doesn't exist.
    Mesh mesh = HeightmapGenerator::generateFromImage("non_existent_file.png", 10.0f, 1.0f);

    // Assert: The resulting mesh should be empty.
    EXPECT_TRUE(mesh.vertices.empty());
    EXPECT_TRUE(mesh.indices.empty());
}

// --- Test Case 2: Simple 3x3 Image ---
// Tests the core logic with a predictable, simple image.
//
// NOTE: This test requires a file named "test_3x3.png"
// to exist in your project's *root* directory (where main.cpp is).
//
// See test/README_TESTING.md for instructions on how to create it.
//
TEST(HeightmapGeneratorTest, GeneratesCorrectlyFrom3x3) {
    // Arrange: Path to the test image
    // We assume the test is run from the 'cmake-build-debug' folder,
    // so we go up one level to find the project root.
    std::string test_image_path = "../../test_3x3.png";

    // Act: Generate a mesh with specific, simple parameters.
    Mesh mesh = HeightmapGenerator::generateFromImage(test_image_path, 10.0f, 1.0f);

    // Assert (General): Check that the file was loaded and mesh generated
    ASSERT_FALSE(mesh.vertices.empty()) << "Test failed. Did you create 'test_3x3.png' in the project root?";
    ASSERT_FALSE(mesh.indices.empty());

    // Assert (Counts): Check that we have the right number of vertices/indices
    // width=3, height=3
    // Vertices = 3 * 3 = 9
    // Indices = (3-1) * (3-1) * 6 = 2 * 2 * 6 = 24
    EXPECT_EQ(mesh.vertices.size(), 9);
    EXPECT_EQ(mesh.indices.size(), 24);

    // Assert (Specifics): Check the vertex data for our known 3x3 image.
    // Our test image is all black (0) except the center (1,1) pixel, which is white (255).
    // The vertex at (x=1, z=1) should be at height 10.0.
    // Its index in the 1D vertex array is (z * width + x) = (1 * 3 + 1) = 4.

    // 1. Check center vertex (index 4)
    const Vertex& centerVertex = mesh.vertices[4];
    EXPECT_FLOAT_EQ(centerVertex.position.x, 1.0f);
    EXPECT_FLOAT_EQ(centerVertex.position.y, 10.0f); // normHeight (1.0) * maxHeight (10.0)
    EXPECT_FLOAT_EQ(centerVertex.position.z, 1.0f);

    // 2. Check corner vertex (index 0)
    const Vertex& cornerVertex = mesh.vertices[0];
    EXPECT_FLOAT_EQ(cornerVertex.position.x, 0.0f);
    EXPECT_FLOAT_EQ(cornerVertex.position.y, 0.0f); // normHeight (0.0) * maxHeight (10.0)
    EXPECT_FLOAT_EQ(cornerVertex.position.z, 0.0f);

    // 3. Check center vertex normal
    // hL=0, hR=0, hD=0, hU=0. All neighbors are 0 height.
    // Normal = normalize(vec3(0 - 0, 2.0 * 1.0, 0 - 0)) = normalize(0, 2, 0) = (0, 1, 0)
    EXPECT_FLOAT_EQ(centerVertex.normal.x, 0.0f);
    EXPECT_FLOAT_EQ(centerVertex.normal.y, 1.0f);
    EXPECT_FLOAT_EQ(centerVertex.normal.z, 0.0f);

    // 4. Check an edge vertex normal (e.g., at (x=1, z=0))
    // Index = (z * width + x) = (0 * 3 + 1) = 1
    // hL = 0 (vertex 0)
    // hR = 0 (vertex 2)
    // hD = 0 (out of bounds)
    // hU = 10.0 (the center peak, vertex 4)
    // Normal = normalize(vec3(0 - 0, 2.0 * 1.0, 0 - 10.0)) = normalize(0, 2, -10)
    const Vertex& topEdgeVertex = mesh.vertices[1];
    glm::vec3 expectedNormal = glm::normalize(glm::vec3(0.0f, 2.0f, -10.0f));
    EXPECT_NEAR(topEdgeVertex.normal.x, expectedNormal.x, 0.0001f);
    EXPECT_NEAR(topEdgeVertex.normal.y, expectedNormal.y, 0.0001f);
    EXPECT_NEAR(topEdgeVertex.normal.z, expectedNormal.z, 0.0001f);
}