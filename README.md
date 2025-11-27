# cub3D 🎮

A raycasting game engine inspired by the world-famous **Wolfenstein 3D** game, which was the first FPS ever. This project is about creating a dynamic 3D environment from a 2D map using raycasting techniques.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge&logo=opengl&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)

## 📖 About

**cub3D** is a 42 School project that introduces raycasting. The goal is to create a realistic 3D graphical representation of the inside of a maze from a first-person perspective using the Ray-Casting principles.

The game engine renders walls with different textures depending on their orientation (North, South, East, West), creates floor and ceiling colors, and allows the player to navigate through the maze using keyboard controls and mouse rotation.

## ✨ Features

- **Raycasting Engine**: Real-time 3D rendering using raycasting algorithm
- **Textured Walls**: Different textures for North, South, East, and West walls
- **Customizable Colors**: Floor and ceiling colors can be set in map files
- **Smooth Movement**: WASD movement with rotation controls
- **Mouse Support**: Optional mouse rotation for looking around
- **FPS Counter**: Real-time frames per second display
- **Map Parser**: Custom `.cub` map file format support
- **Distance Shading**: Walls darken based on distance for depth perception

## 🛠️ Technologies

| Technology | Description |
|------------|-------------|
| **C** | Primary programming language |
| **MLX42** | Modern cross-platform graphics library for OpenGL |
| **GLFW** | Library for OpenGL context, window, and input management |
| **libft** | Custom C standard library (turbo_libft) |
| **CMake** | Build system for MLX42 |
| **Make** | Build automation tool |

### Core Algorithms & Concepts

- **Raycasting**: Digital Differential Analyzer (DDA) algorithm for ray-wall intersection
- **Texture Mapping**: Projecting 2D textures onto 3D walls
- **Field of View (FOV)**: 60-degree viewing angle
- **Distance-based Shading**: Color attenuation based on distance

## 📁 Project Structure

```
cub3d/
├── include/
│   └── cub.h              # Header file with structures and prototypes
├── srcs/
│   ├── main.c             # Entry point and initialization
│   ├── parsing/           # Map and data parsing
│   │   ├── get_data.c     # Parse textures and colors
│   │   ├── map.c          # Map parsing and validation
│   │   ├── verif.c        # Syntax verification
│   │   ├── flood_fill.c   # Map validity check
│   │   └── player_utils.c # Player position handling
│   ├── raycasting/        # Rendering engine
│   │   ├── init_raycasting.c  # MLX setup and main loop
│   │   ├── draw_wall.c    # Wall rendering with textures
│   │   ├── input.c        # Keyboard and mouse input
│   │   └── utils.c        # Raycasting utilities
│   ├── utils/             # Utility functions
│   │   ├── utils.c
│   │   ├── utils_parsing.c
│   │   └── free.c
│   └── bonus_mouse_rotate.c   # Mouse rotation feature
├── maps/
│   ├── good/              # Valid test maps
│   ├── bad/               # Invalid maps for testing
│   └── textures/          # Wall texture PNG files
├── MLX42/                 # Graphics library (submodule)
├── turbo_libft/           # Custom C library (submodule)
└── makefile               # Build configuration
```

## 🚀 Installation

### Prerequisites

- GCC or Clang compiler
- CMake (for MLX42)
- GLFW library
- Make

### macOS

```bash
# Install dependencies using Homebrew
brew install glfw cmake

# Clone the repository with submodules
git clone --recursive https://github.com/h-claude/cub3d.git
cd cub3d

# Build the project
make
```

### Linux

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential cmake libglfw3-dev libglfw3

# Clone and build
git clone --recursive https://github.com/h-claude/cub3d.git
cd cub3d
make
```

## 🎮 Usage

```bash
./cub3D maps/good/map.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `M` | Toggle mouse rotation |
| `ESC` | Exit game |

## 🗺️ Map Format

Maps use the `.cub` file extension with the following format:

```
NO ./path/to/north_texture.png
SO ./path/to/south_texture.png
WE ./path/to/west_texture.png
EA ./path/to/east_texture.png

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11000000110101011100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11111111 1111111 111111111111
```

### Map Elements

| Symbol | Description |
|--------|-------------|
| `1` | Wall |
| `0` | Empty floor space |
| `N` | Player start (facing North) |
| `S` | Player start (facing South) |
| `E` | Player start (facing East) |
| `W` | Player start (facing West) |
| ` ` | Empty space (outside map) |

### Configuration

| Identifier | Description |
|------------|-------------|
| `NO` | North wall texture path |
| `SO` | South wall texture path |
| `WE` | West wall texture path |
| `EA` | East wall texture path |
| `F` | Floor color (R,G,B) |
| `C` | Ceiling color (R,G,B) |

## ⚙️ Configuration Constants

Defined in `include/cub.h`:

```c
#define WIDTH 1920           // Window width
#define HEIGHT 1080          // Window height
#define FOV 60               // Field of view in degrees
#define MOVE_SPEED 0.05      // Player movement speed
#define MOUSE_SENSITIVITY 0.00075  // Mouse sensitivity
```

## 🧹 Makefile Commands

```bash
make        # Build the project
make clean  # Remove object files
make fclean # Remove all generated files
make re     # Rebuild the project
```

## 👥 Contributors

- **hclaude** - [@h-claude](https://github.com/h-claude) - 42 Mulhouse
- **aurban** - [@aurban](https://github.com/Anantiz) - 42 Mulhouse

## 📚 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42)
- [42 Cursus](https://42.fr/)

## 📄 License

This project is part of the 42 School curriculum. Feel free to use it as a reference for your own cub3D implementation.

---

Made with ❤️ at [42 Mulhouse](https://42mulhouse.fr/)
