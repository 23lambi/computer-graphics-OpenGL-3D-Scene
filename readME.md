# OpenGL 3D Scene

An interactive 3D scene built with OpenGL and GLUT featuring three objects, real-time controls, and dual projection modes.  
**Lampros Patas | A.M. 2890**

## Compile & Run

```bash
clang++ main.cpp scene.cpp welcome.cpp ui.cpp -framework OpenGL -framework GLUT -o app
./app
```

> Requires macOS with the built-in GLUT framework (Xcode Command Line Tools).

## File Structure

| File | Description |
|------|-------------|
| `main.cpp` | GLUT initialization, all callbacks (display, keyboard, mouse, idle), menu setup, main loop |
| `scene.cpp / .h` | Object rendering (cube, sphere, polygon), axes, floor, color logic |
| `ui.cpp / .h` | 2D HUD overlay with controls panel, colors panel, and status bar |
| `welcome.cpp / .h` | Welcome splash screen with centered bitmap text |
| `app_state.h` | Shared global state via `extern` declarations |

## Controls

| Input | Action |
|-------|--------|
| `1` / `2` / `3` | Select object: Cube / Sphere / 2D Polygon |
| `←` `→` `↑` `↓` | Rotate active object (Y and X axis, ±5° per step) |
| `+` / `-` | Scale up / down (range 0.3–2.0, step 0.1) |
| `Space` | Toggle Auto Rotate |
| `P` | Toggle Perspective ↔ Orthographic projection |
| `C` `R` `G` `O` `M` | Set color: Cyan / Red / Green / Orange / Multicolor |
| `S` or `Enter` | Dismiss welcome screen |
| `Esc` | Exit |
| `Shift` + Left Drag | Zoom (adjusts camera distance or ortho zoom) |
| Right Click | Context menu: object, color, rotation |

## Features

- **3 Objects**: Hand-built cube (GL_QUADS, per-face normals), GLUT sphere (30 slices/stacks), flat 2D polygon (GL_POLYGON, 40 segments)
- **Projections**: Perspective (`gluPerspective`, FOV 60°) and Orthographic (`glOrtho`) with dynamic switching
- **Camera**: `gluLookAt(6, 4.5, dist)` with Shift+Drag zoom for both projection modes
- **Lighting**: `GL_LIGHT0` at (4, 6, 4) with ambient / diffuse / specular + `GL_COLOR_MATERIAL`
- **5 Color Modes**: Default, Cyan, Red, Green, Orange, Multicolor (per-face on cube, `sin(time)` iridescent on sphere/polygon)
- **Auto Rotate**: `glutIdleFunc` increments Y rotation by 0.2°/frame on the active object
- **HUD Overlay**: 2D semi-transparent panels via `gluOrtho2D` showing controls, colors, and live status
- **Active Object Highlight**: Selected object rendered at 1.15× scale

---

## Running on Windows

The code **does not run directly on Windows** due to macOS-specific includes and frameworks. Three changes are needed:

### 1. Change the include (in all `.cpp` files)

```cpp
// Replace:
#include <GLUT/glut.h>

// With:
#include <GL/glut.h>
```

### 2. Install freeglut

Download [freeglut for Windows](https://www.transmissionzero.co.uk/software/freeglut-devel/) or via vcpkg:

```bash
vcpkg install freeglut
```

### 3. Compile with MinGW/g++

```bash
g++ main.cpp scene.cpp welcome.cpp ui.cpp -lfreeglut -lopengl32 -lglu32 -o app.exe
```

> With **Visual Studio**: add the `.cpp` files to a project and link `freeglut.lib`, `opengl32.lib`, `glu32.lib`.

> The rendering logic and visuals remain **exactly the same** — only the includes and linking differ.