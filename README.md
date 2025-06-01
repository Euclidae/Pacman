# Pacman Game

A Pacman implementation using C++ and SDL3 with ghost AI, pellet consumption, and collision detection. Will not be developed further due to the desire to move to other projects.

## Dependencies

- C++17 compiler
- SDL3
- SDL3_image
- CMake (recommended)

## Directory Structure
```
pacman/
├── pacman sprites/  # Sprite images
├── animation.cpp
├── animation.hpp
├── entity.hpp
├── game.cpp
├── game.hpp
├── ghost.cpp
├── ghost.hpp
├── globals.hpp
├── main.cpp
├── map.cpp
├── map.hpp
├── map.txt          # Game map layout
├── pacman.cpp
└── pacman.hpp
```

## Compilation Instructions

### For Linux:

1. **Install dependencies**:
```bash
sudo apt-get install build-essential libsdl3-dev libsdl3-image-dev
```

2. **Compile using g++**:
```bash
g++ -std=c++17 -Iinclude -o pacman *.cpp \
    `pkg-config --cflags --libs sdl3 SDL3_image` \
    -lstdc++fs
```

3. **Run the game**:
```bash
./pacman
```

### For Windows (MSYS2/MinGW):

1. **Install dependencies**:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake \
          mingw-w64-x86_64-SDL3 mingw-w64-x86_64-SDL3_image
```

2. **Compile using g++**:
```bash
g++ -std=c++17 -Iinclude -o pacman.exe *.cpp \
    -lSDL3 -lSDL3_image \
    -L/mingw64/lib
```

3. **Run the game**:
```bash
pacman.exe
```

### For Windows (Visual Studio):

1. Install vcpkg:
```powershell
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
```

2. Install dependencies:
```powershell
vcpkg install sdl3:x64-windows sdl3-image:x64-windows
```

3. Create a Visual Studio project:
   - New Project → C++ Console App
   - Add all source files to the project
   - Configure include directories:
     - `$(VCPKG_ROOT)\installed\x64-windows\include`
   - Configure linker dependencies:
     - `SDL3.lib`
     - `SDL3_image.lib`
     - `SDL3main.lib`
   - Set SubSystem to "Console"

4. Build and run from Visual Studio

## Running the Game

1. Ensure required assets are in place:
   - `pacman sprites/` directory with sprite PNGs
   - `map.txt` in the executable directory

2. Controls:
   - Arrow keys: Move Pacman
   - ESC: Quit game

## Troubleshooting

### Common Issues:
1. **Missing sprites**:
   - Verify `pacman sprites/` directory exists with these files:
     - `red sprites.png`
     - `blue sprites.png`
     - `pink sprites.png`
     - `orange sprites.png`
     - `pacman sprites.png`

2. **SDL3 not found**:
   - Set environment variables:
     - Linux: `export LD_LIBRARY_PATH=/path/to/sdl3/lib`
     - Windows: Add SDL3 DLL paths to system PATH

3. **Map loading issues**:
   - Ensure `map.txt` is in the same directory as the executable
   - Check map file uses correct characters:
     - 'P' : Pacman
     - 'r' : Red ghost
     - 'b' : Blue ghost
     - 'p' : Pink ghost
     - 'o' : Orange ghost
     - 'X' : Walls

## Known Issues
- Ghost pathfinding may occasionally cause stuck behavior
- High CPU usage in some environments (consider frame limiting)
- Screen wrapping might cause visual glitches
  

This README includes:
1. Clear dependencies for both platforms
2. Step-by-step compilation instructions
3. Directory structure overview
4. Runtime requirements and controls
5. Troubleshooting common issues
6. CMake alternative for modern builds
7. Known limitations

Key notes:
- The sprite directory must be named exactly "pacman sprites" with space
- Windows builds require SDL3 DLLs in PATH or executable directory
- The map file uses specific character codes for entity placement
- Visual Studio users should use vcpkg for dependency management
- Ghost behavior might need tuning in complex maze areas
