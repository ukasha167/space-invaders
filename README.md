# Space Invaders 2.5D (C/Raylib)

A high-performance, minimalist 2.5D space shooter built in pure C11 using the Raylib framework. This project was developed with a focus on systems-level architecture, manual memory management, and hardware-efficient rendering.

## Technical Highlights

- **Object Pooling:** Implements a "rounding buffer" system for lasers and meteors. This avoids expensive heap allocations during the game loop, ensuring zero garbage collection pauses and consistent frame times.
- **Infinite Grid Snapping:** Uses a camera-tethered grid translation algorithm. The grid origin snaps to the camera's integer coordinates, providing the illusion of an infinite horizon without the performance cost of large-scale geometry.
- **Cinematic Follow Camera:** A custom over-the-shoulder perspective inspired by modern third-person action titles (e.g., RDR2). Features a 48.0 FOV and asymmetric X-offset for a grounded, cinematic feel.
- **Sphere Collision Detection:** Optimized sphere-to-sphere collision logic that culls inactive objects before calculation, providing a fast and mathematically stable way to handle projectile and player hits.
- **C11 Architecture:** Designed using a modular header/source split with strict control over global state via `extern` and `static` scoping.

## Project Structure

- `main.c`: Entry point and top-level game state synchronization.
- `renderer.c / .h`: GPU context management, window initialization, and the 2.5D drawing pipeline.
- `solver.c / .h`: Physics updates, collision detection logic, and camera stabilization.
- `spaceship.c / .h`: Player movement logic and 3D model state.
- `lazer.c / .h`: Projectile lifecycle management and object pooling.
- `meteor.c / .h`: Procedural meteor generation and recycling.
- `defines.c / .h`: Centralized constants, hardware settings, and global configuration.

## Controls

- **A / D**: Move Left / Right
- **SPACE**: Fire Laser

## Build Instructions

### Prerequisites
- **CMake** (v3.24+)
- **C Compiler** (Clang, GCC, or MSVC)
- **Raylib** (Handled automatically via `FetchContent` in CMake)

### Compilation
From the project root, run:

```bash
mkdir build
cd build

# It will download the raylib
cmake .. 

# Compile the project
cmake --build .
```
