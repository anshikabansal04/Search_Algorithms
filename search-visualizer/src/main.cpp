#include "raylib.h"

#include "Grid.h"

int main() {
    // --- grid setup ---------------------------------------------------------
    constexpr int kRows = 20;
    constexpr int kCols = 30;
    constexpr int kCellSize = 28;

    Grid grid(kRows, kCols, kCellSize);

    // --- window -------------------------------------------------------------
    InitWindow(grid.pixelWidth(), grid.pixelHeight(), "Search Visualizer");
    SetTargetFPS(60);

    // --- render loop --------------------------------------------------------
    // Everything algorithm-related goes in here: read input, update cell
    // colours via grid.set(...), and it draws automatically.
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
