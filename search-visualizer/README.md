# Search Visualizer

A minimal C++ / [raylib](https://www.raylib.com/) starting point for visualizing
graph-search algorithms (BFS, Dijkstra, A\*, …) on a 2D grid.

This repo is **visualization scaffolding only** — it opens a window and draws a
grid. The algorithm logic is yours to add.

## Requirements

- A C++17 compiler (clang/gcc/MSVC)
- [CMake](https://cmake.org/) ≥ 3.15
- Git (raylib is fetched from GitHub at configure time)

No manual raylib install needed — CMake's `FetchContent` downloads and builds it
automatically on the first configure.

## Build & run

```bash
mkdir build && cd build
cmake ..        # first run clones + builds raylib (~1–2 min); cached afterwards
make
./bin/visualizer
```

The first `cmake ..` clones raylib into `build/_deps/`. Later `cmake ..` / `make`
runs reuse it — it is **not** re-downloaded unless you delete `build/`.

## Project layout

```
search-visualizer/
├── CMakeLists.txt     # build config + raylib FetchContent
├── include/
│   └── Grid.h         # Grid: size, per-cell color, draw, pixel→cell mapping
└── src/
    ├── Grid.cpp       # Grid implementation
    └── main.cpp       # window creation + render loop
```

`file(GLOB ... src/*.cpp)` means **any `.cpp` you drop into `src/` is compiled
automatically** — no need to edit `CMakeLists.txt` when you add a file.

## What it draws

A 20×30 grid of light tiles with grid lines, in an 840×560 window. Edit the
constants at the top of `src/main.cpp` to change dimensions:

```cpp
constexpr int kRows = 20;
constexpr int kCols = 30;
constexpr int kCellSize = 28;
```

## How to build on it

The `Grid` knows nothing about algorithms — it just stores a color per cell and
draws itself. Your algorithm drives the visualization by setting cell colors.

Key API (`include/Grid.h`):

| Call | Purpose |
|------|---------|
| `grid.set(row, col, color)` | Paint a cell (visited, frontier, wall, path, …) |
| `grid.at(row, col)`         | Read a cell's current color |
| `grid.cellAtPixel(x, y, row, col)` | Map a screen pixel to a cell (returns `false` if outside) |
| `grid.draw()`               | Draw all cells + grid lines |
| `grid.rows() / cols() / cellSize()` | Dimensions |
| `grid.pixelWidth() / pixelHeight()` | Window size in pixels |

The render loop in `src/main.cpp` is where per-frame logic lives:

```cpp
while (!WindowShouldClose()) {
    // 1. Input — e.g. place walls / start / goal:
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int r, c;
        if (grid.cellAtPixel(GetMouseX(), GetMouseY(), r, c))
            grid.set(r, c, BLACK);
    }

    // 2. Step your algorithm one node and color the cell it expands:
    //    grid.set(node.row, node.col, SKYBLUE);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    grid.draw();
    EndDrawing();
}
```

Useful raylib calls for this: `GetMouseX()/GetMouseY()`, `IsMouseButtonPressed()`,
`IsKeyPressed()`, `GetFrameTime()`. Full cheatsheet: <https://www.raylib.com/cheatsheet/cheatsheet.html>.

## Tips

- **Animate over frames**, not all at once: expand one (or N) search node per
  frame so you can watch the frontier grow.
- **Color convention** is up to you — e.g. grey = wall, sky blue = visited,
  yellow = frontier, magenta = path, green = start, red = goal.
- To keep raylib cached across a `rm -rf build`, add to `CMakeLists.txt`:
  ```cmake
  set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/.deps" CACHE PATH "")
  ```
