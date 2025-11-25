#include <iostream>

#include "HeightmapGenerator.h"
#include "Mesh.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <heightmap_image_file>" << std::endl;
        return 1;
    }

    std::cout << "Generating mesh from heightmap..." << std::endl;
    float terrainMaxHeight = 40.0f;
    float terrainScaleXZ = 1.0f;
    Mesh terrainMesh = HeightmapGenerator::generateFromImage((argv[1]), terrainMaxHeight, terrainScaleXZ);

    if (terrainMesh.vertices.empty()) {
        std::cerr <<  "Failed to generate mesh." << std::endl;
        return 1;
    }

    std::cout << "Generated " << terrainMesh.vertices.size() << " verticies and " << terrainMesh.indices.size() << " indices." << std::endl;

    std::cout << "Shutting down." << std::endl;
}
