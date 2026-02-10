# Erosion - Terrain Viewer

## Build Commands

CMake is not in PATH. Use CLion's bundled cmake:

```bash
# Build the project
"C:/Program Files/JetBrains/CLion 2025.2.3/bin/cmake/win/x64/bin/cmake.exe" --build "C:/Users/wenze/CLionProjects/erosion/cmake-build-debug" --target erosion

# Run the application
./cmake-build-debug/erosion.exe <heightmap_image_file>
```

## Architecture

The project uses dependency injection with interfaces for testability:

- `IWindow` → `GlfwWindow` - Window management (GLFW)
- `IRenderer` → `OpenGLRenderer` - OpenGL rendering
- `IShader` → `OpenGLShader` - Shader compilation/uniforms
- `IMeshGenerator` → `HeightmapGenerator` - Mesh generation from heightmaps
