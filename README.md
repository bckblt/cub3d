# cub3d

A raycasting engine written in C, inspired by Wolfenstein 3D — renders a first-person 3D view of a maze from a 2D map, using the MiniLibX graphics library.

## About

`cub3d` is a 42 School project that introduces the fundamentals of 3D graphics through raycasting. A 2D top-down map (walls, empty space, player position/orientation) is parsed from a custom `.cub` config file and rendered in real time as a first-person 3D scene, using ray casting to determine wall distances and heights per column of the screen.

The project reuses two previously built 42 libraries — `libft` and `get_next_line` (`gnl`) — and includes automated test scripts for validating map parsing.

## Project structure

| Path | Description |
|---|---|
| `main.c` | Entry point — initializes the game and starts the main loop |
| `engine.c` | Core raycasting engine — casts rays and computes wall distances per column |
| `render_frame.c` | Renders a full frame to the window using the raycasting results |
| `init_player.c` | Initializes player position, orientation, and movement state |
| `player_rotate.c` | Handles player rotation (turning) |
| `minimap.c` | Renders the 2D minimap overlay |
| `load_textures.c` | Loads and manages wall textures |
| `cub3d.h` | Struct/type definitions and function prototypes |
| `parse/` | Map (`.cub` file) parsing and validation |
| `maps/` | Sample map files used to test the engine |
| `textures/` | Wall texture assets |
| `libft/` | Custom C standard library |
| `gnl/` | Custom `get_next_line` implementation, used to parse map/config files |
| `minilibx-linux/` | MiniLibX graphics library (Linux version) |
| `test_good_maps.sh` / `test_bad_maps.sh` | Shell scripts for testing valid/invalid map files |
| `Makefile` | Build rules for the project |

## Compilation

```bash
make        # builds the cub3D executable
make clean  # removes object files
make fclean # removes object files and the executable
make re     # rebuilds everything from scratch
```

## Usage

```bash
./cub3D maps/map.cub
```

Controls:
- `W` / `A` / `S` / `D` — move forward/left/backward/right
- Left / Right arrow keys — rotate the camera
- `ESC` or window close button — exit

## Map (`.cub`) format

A `.cub` file defines texture paths, floor/ceiling colors, and the map layout:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

1111111111
1000000001
1000N00001
1000000001
1111111111
```

The map must be surrounded by walls, contain exactly one player start position (`N`, `S`, `E`, or `W` for orientation), and be a closed, reachable space.

## Testing

```bash
./test_good_maps.sh   # runs the engine against valid maps
./test_bad_maps.sh    # runs the engine against invalid maps (should be rejected)
```

## Resources

While building and debugging this project, the following resources were especially helpful:

- **[Bash Reference Manual / GNU User Manuals](https://www.gnu.org/software/bash/manual/)** — used for understanding shell scripting for the map test scripts and general shell/process behavior around the build.
- **[Stack Overflow](https://stackoverflow.com/)** — used to troubleshoot raycasting math (DDA algorithm, ray-wall intersection, texture mapping), MiniLibX event handling, and memory management for textures/images.

## Author

[bckblt](https://github.com/bckblt) — 42 School
