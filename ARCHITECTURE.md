# Architecture

This is a C++20 OpenGL terrain renderer intended to eventually simulate hydraulic erosion. It loads a grayscale heightmap image, converts it into a 3D triangle mesh, and renders it with Phong lighting.

## Project Structure

```
erosion/
├── main.cpp                  # Entry point and render loop
├── Vertex.h                  # Vertex data structure
├── Mesh.h                    # CPU-side mesh container
├── HeightmapGenerator.h/.cpp # Heightmap image → Mesh conversion
├── Renderer.h/.cpp           # GPU upload and draw calls (OpenGL)
├── Shader.h/.cpp             # GLSL shader compilation and uniforms
├── Window.h/.cpp             # GLFW window and OpenGL context
├── terrain.vert              # Vertex shader (MVP transform)
├── terrain.frag              # Fragment shader (Phong + height color)
├── stb_image_impl.cpp        # STB image library implementation unit
├── CMakeLists.txt            # Build system
└── test/
    └── test_heightmap_generator.cpp  # Google Test unit tests
```

## System Overview

```
Heightmap Image (PNG/JPG)
        │
        ▼
 HeightmapGenerator          (CPU)
        │  stbi_load → pixel grid → Mesh (vertices + indices)
        ▼
    Renderer                  (CPU → GPU)
        │  createRenderableMesh → VAO / VBO / IBO
        ▼
  Render Loop                 (main.cpp)
        │  Shader uniforms (MVP matrices, camera pos)
        │  Renderer::draw → glDrawElements
        ▼
  terrain.vert / terrain.frag (GPU)
        │  MVP transform → Phong lighting → height-based color
        ▼
      Window                  (GLFW)
           swapBuffers → display
```

## Data Flow

### 1. Mesh Generation (`HeightmapGenerator`)

`HeightmapGenerator::generateFromImage(filepath, maxHeight, scaleXZ)` converts a heightmap image into a `Mesh`:

- Each pixel maps to one `Vertex`:
  - `position`: `(x * scaleXZ, normalizedBrightness * maxHeight, z * scaleXZ)`
  - `normal`: computed via finite differences of neighboring pixel heights
  - `texCoords`: UV normalized to `[0, 1]`
- Indices form a triangle grid — two triangles (six indices) per quad cell

### 2. GPU Upload (`Renderer`)

`Renderer::createRenderableMesh(mesh)` uploads CPU data to the GPU:

- Creates a VAO with three vertex attributes:
  - Location 0: `position` (vec3)
  - Location 1: `normal` (vec3)
  - Location 2: `texCoords` (vec2)
- Returns a `RenderableObject` (VAO/VBO/IBO handles + index count)

### 3. Shaders

`terrain.vert` applies a standard MVP transform and forwards world-space position, normal, and height to the fragment shader.

`terrain.frag` computes Phong lighting (ambient + diffuse + specular) against a hardcoded sun direction `(0.5, 1.0, 0.5)` and blends terrain color from dark green (low) to white (high) based on the vertex Y coordinate.

### 4. Render Loop (`main.cpp`)

Each frame:
1. `Window::pollEvents()`
2. `Renderer::beginFrame()` — clears color and depth buffers
3. `Shader::use()` + set uniforms (`uModel`, `uView`, `uProjection`, `uViewPos`)
4. `Renderer::draw()` — `glDrawElements(GL_TRIANGLES, ...)`
5. `Window::swapBuffers()`

## Key Data Structures

| Type | Location | Purpose |
|---|---|---|
| `Vertex` | `Vertex.h` | `vec3 position`, `vec3 normal`, `vec2 texCoords` |
| `Mesh` | `Mesh.h` | CPU-side `vector<Vertex>` + `vector<unsigned int>` indices |
| `RenderableObject` | `Renderer.h` | GPU handle struct: VAO, VBO, IBO IDs + index count |

## Dependencies

All dependencies are fetched automatically via CMake `FetchContent` — no manual installation required.

| Library | Version | Role |
|---|---|---|
| OpenGL | 3.3 Core | GPU rendering API |
| GLAD (libigl) | master | OpenGL function pointer loader |
| GLFW | 3.4 | Window creation, input, OpenGL context |
| GLM | 1.0.2 | Math types (vec2, vec3, mat4) |
| STB Image | master | PNG/JPEG heightmap loading |
| Google Test | v1.17.0 | Unit testing |

## Build

```bash
cmake -B cmake-build-debug
cmake --build cmake-build-debug
```

Run with a heightmap image path as the only argument:

```bash
./cmake-build-debug/erosion path/to/heightmap.png
```
