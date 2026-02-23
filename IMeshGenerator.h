//
// Created for dependency injection support
//

#pragma once

#include "Mesh.h"
#include <string>

/**
 * @brief Interface for generating a mesh from a heightmap image.
 *
 * Abstracts mesh generation to allow dependency injection and testing.
 */
class IMeshGenerator {
public:
  virtual ~IMeshGenerator() = default;

  /**
   * @brief Generates a terrain mesh from a heightmap image file.
   * @param filepath   Path to the heightmap image.
   * @param maxHeight  Maximum vertex height in world units.
   * @param scaleXZ    Scale factor applied to the X and Z axes.
   * @return The generated Mesh.
   */
  virtual Mesh generate(const std::string &filepath, float maxHeight,
                        float scaleXZ) = 0;
};
