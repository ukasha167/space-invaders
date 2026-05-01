# Space Shooters

<p align="center">
  <img src="./assets/demo.gif" alt="Demo" width="700"/>
</p>

A high-performance, Synthwave-inspired 3D space shooter built in **C** using **Raylib**. Implements a **Data-Oriented Design (DOD)** architecture with a custom rendering pipeline and optimized collision mathematics.

---

## Table of Contents

- [Technical Highlights](#technical-highlights)
- [Getting Started](#getting-started)
- [Architecture & Design](#architecture--design)
- [Controls](#controls)
- [License](#license)

---

## Technical Highlights

| Feature | Implementation |
| :--- | :--- |
| **Data-Oriented Architecture** | Structure of Arrays (SoA) for maximum CPU cache efficiency and SIMD-readiness |
| **Custom Rendering Pipeline** | Halation floor effect via `rlgl` vertex interpolation and Additive Blending |
| **Optimized Collision Math** | Compile-time constant radii and squared-distance comparisons eliminating `sqrt()` overhead |
| **Shared Mesh Architecture** | Single VRAM footprint across all entity instances via mesh ownership pattern |
| **GLSL Shader Integration** | Real-time fragment shaders for hit-flash effects, driven by CPU-GPU uniform bridge |

---

## Getting Started

### Prerequisites

You will need **Clang/GCC** (or MSVC on Windows), **CMake**, and **Raylib**.

#### macOS

Install via Homebrew:

```bash
brew install raylib cmake
```

#### Linux (Debian / Ubuntu)

Install the required system dependencies, then build Raylib from source or install via your package manager:

```bash
sudo apt update
sudo apt install build-essential cmake libraylib-dev
```

> If `libraylib-dev` is unavailable in your distribution's repos, install Raylib manually from [raylib.com](https://www.raylib.com) or via the official GitHub releases.

#### Windows

1. Install [CMake](https://cmake.org/download/) and add it to your system `PATH`
2. Install [MinGW-w64](https://www.mingw-w64.org/) (GCC for Windows) or use the [MSVC toolchain](https://visualstudio.microsoft.com/visual-cpp-build-tools/) via Visual Studio Build Tools
3. Download the prebuilt Raylib binaries for Windows from [raylib.com](https://www.raylib.com) and note the install path — you will need it during the CMake configuration step

---

### Installation

```bash
git clone https://github.com/ukasha167/space-shooters.git
cd space-shooters
```

---

### Building

#### macOS & Linux

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

#### Windows (MinGW)

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/path/to/raylib"
cmake --build .
```

#### Windows (MSVC)

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH="C:/path/to/raylib"
cmake --build . --config Release
```

Or just open the project in Visual Studio, it will automatically download the dependencies. After it's completed, hit play.

---

### Running

#### macOS & Linux

```bash
./main
```

#### Windows

```bash
main.exe
```

---

## Architecture & Design

### I. Data-Oriented Design — Structure of Arrays (SoA)

Traditional game entities use **Array of Structures (AoS)** — each entity is a self-contained object holding all its own fields. SoA inverts this: each *attribute* gets its own contiguous array.

```
AoS:  [pos, speed, active, rot] [pos, speed, active, rot] [pos, speed, active, rot]
SoA:  [pos, pos, pos]  [speed, speed, speed]  [active, active, active]
```

When the update loop iterates positions, the CPU cache line is packed exclusively with position data — no cache pollution from cold fields like rotation axes. This is the foundation for potential SIMD vectorization in future iterations.

---

### II. Halation Rendering Pattern

Full-screen bloom post-processing is expensive. This project achieves a Synthwave neon glow through a **Layered Additive Pipeline** at near-zero overhead:

- Vertices are manually defined via `rlgl` with alpha gradients baked in
- Rendered under `BLEND_ADDITIVE` mode, causing overlapping fragments to sum their color values
- The GPU produces a bright, saturated core that bleeds naturally into the surrounding void

No framebuffer copies. No ping-pong render targets. Pure per-vertex math.

---

### III. Collision System

Collision detection implements a high-performance, **two-phase spatial pipeline** optimized for a Data-Oriented architecture. Since the game is constrained to a fixed horizontal plane, the system flattens 3D sphere tests into optimized 2D circular tests, ignoring the $Y$ axis entirely to save clock cycles.

#### 1. Broad-Phase: Early-Out AABB Pruning
Before committing to any heavy math, the system performs a "Broad-Phase" check using Axis-Aligned Bounding Boxes (AABB). By simply comparing the absolute difference of the $X$ and $Z$ coordinates against the combined radii, we can discard roughly 90% of potential collisions using only basic subtraction.
```c
// Step 1: Horizontal distance check (Broad-Phase)
float dx = lx - meteors.pos[j].x;
if (dx > totalRadius || dx < -totalRadius) continue; // Early Out

float dz = lz - meteors.pos[j].z;
if (dz > totalRadius || dz < -totalRadius) continue; // Early Out
```

#### 2. Narrow-Phase: Squared-Distance Elimination
Only if the Broad-Phase passes does the system enter the "Narrow-Phase." Here, we use the Pythagorean theorem to check for a precise hit. To maximize efficiency, we compare **squared distances** to bypass the computationally expensive Square Root (`sqrtf`) operation.
```c
// Step 2: Squared distance check (Narrow-Phase)
// No sqrt() required:
float distSq = (dx * dx) + (dz * dz);
if (distSq < (totalRadius * totalRadius)) {
    // Collision Confirmed
}
```

#### Technical Optimizations:
*   **Dynamic Radius Scaling:** Unlike static implementations, the `totalRadius` is calculated at runtime by multiplying the base `METEOR_RADIUS` by the meteor's individual `scale`. This allows for pixel-perfect collisions on varied asteroid sizes.
*   **Register Locality:** Laser positions (`lx`, `lz`) are pulled into local variables before the inner loop starts. This encourages the compiler to keep this "hot" data in CPU registers, minimizing memory fetches during the scan of the meteor arrays.
*   **Short-Circuit Logic:** The moment a laser registers a hit, the inner loop `breaks`. A spent laser has no business checking the remaining meteors, significantly reducing the average-case complexity.

---

### IV. Shared Mesh Architecture

Raylib's `UnloadModel()` frees the underlying mesh data. Naively sharing one mesh pointer across multiple `Model` structs causes a **double-free crash** on cleanup.

**Solution — Ownership Hijacking:**

One model is designated the master owner. All secondary `Model` shells reference the same mesh pointer but have their `.meshCount` set to `0` before cleanup. Raylib's unload routine skips mesh deallocation when the count is zero, leaving the vertex data intact until the master owner releases it last.

This keeps VRAM usage at a single mesh upload regardless of how many model shells reference it.

---

## Controls

| Action | Input |
| :--- | :--- |
| Move | `A` `D` / `<–` `–>`|
| Shoot | `Space` |
| Start | `Space` |

---

## License

Distributed under the **MIT License** — see [`LICENSE`](LICENSE) for details.
