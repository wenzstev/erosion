# Erosion - Terrain Viewer

## Build Commands

CMake is not in PATH. Use CLion's bundled cmake:

```bash
# Build the project
"C:/Program Files/JetBrains/CLion 2025.2.3/bin/cmake/win/x64/bin/cmake.exe" --build "C:/Users/wenze/CLionProjects/erosion/cmake-build-debug" --target erosion

# Run the application
./cmake-build-debug/erosion.exe <heightmap_image_file>
```

## Contribution Requirements

Every commit that adds or changes functionality must include:

- **Doxygen docs** — all new public structs, classes, and functions require `@brief` (and `@param`/`@return` where applicable) comments matching the style already used in the codebase.
- **Unit tests** — new CPU-side logic (mesh generation, data transforms, utilities) must have corresponding tests in `test/`. Tests are not required for code that depends on a live OpenGL context (e.g. renderer, shader, window), but any testable logic extracted from those layers must be covered.

## Architecture

> **Keep this section up to date.** Whenever you add, remove, or significantly change an interface, implementation, data structure, build target, or dependency, update the relevant parts of this section before committing.

All core subsystems are abstracted behind interfaces and injected into `Application`, enabling loose coupling and testability.

### Interfaces → Implementations

| Interface | Implementation | Responsibility |
|---|---|---|
| `IWindow` | `GlfwWindow` | Window lifecycle, input polling, buffer swap |
| `IRenderer` | `OpenGLRenderer` | Frame management, mesh upload/draw |
| `IShader` | `OpenGLShader` | GLSL compilation, linking, uniform upload |
| `IMeshGenerator` | `HeightmapGenerator` | Terrain mesh generation from heightmap images |

### Data Structures

- **`Vertex`** (`Vertex.h`) — position, normal, texCoords (all `glm` types)
- **`Mesh`** (`Mesh.h`) — CPU-side `vertices` and `indices` vectors
- **`RenderableObject`** (`IRenderer.h`) — move-only struct holding `GLVertexArray vao`, `GLBuffer vbo`, `GLBuffer ibo`, and `indexCount`; GPU resources are released automatically on destruction
- **`GLVertexArray` / `GLBuffer`** (`GLHandles.h`) — move-only RAII wrappers; call `glDeleteVertexArrays` / `glDeleteBuffers` in their destructors
- **`AppConfig`** (`AppConfig.h`) — immutable configuration (paths, window size, terrain parameters)

### Application

`Application` (`Application.h/.cpp`) owns all subsystems via `std::unique_ptr` to their interfaces. It constructs the camera matrices, orchestrates the render loop, and holds the terrain `Mesh` and `RenderableObject`.

### Build Targets

- **`terrain_lib`** (static library) — `Window`, `Renderer`, `Shader`, `HeightmapGenerator`; links glad, glfw, glm, stb_image
- **`erosion`** (executable) — `Application` + `main`; links `terrain_lib`
- **`erosion_tests`** (executable) — GoogleTest suite in `test/`; links `terrain_lib`

### External Dependencies

glfw 3.4 · glad · glm 1.0.2 · stb (stb_image) · googletest 1.17.0
