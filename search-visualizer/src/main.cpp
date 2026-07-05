#include "raylib.h"
#include "Grid.h"
#include "Search.h"
#include<vector>
int main() {

    Search search;
  
    // --- grid setup ---------------------------------------------------------
    constexpr int kRows = 20;
    constexpr int kCols = 30;
    constexpr int kCellSize = 28;

    Grid grid(kRows, kCols, kCellSize);

    // --- window -------------------------------------------------------------
    InitWindow(grid.pixelWidth(), grid.pixelHeight(), "Search Visualizer");
    SetTargetFPS(60);
vector<vector<Node>> nodes(
    kRows,
    vector<Node>(kCols)
);
for(int r = 0; r < kRows; r++)
{
    for(int c = 0; c < kCols; c++)
    {
        nodes[r][c].row = r;
        nodes[r][c].col = c;
    }
}
// Vertical wall in the middle
for(int r = 0; r < 18; r++)
{
    nodes[r][15].obstacle = true;
    grid.set(r,15,BLACK);
}
Node* start = &nodes[0][0];
Node* end = &nodes[19][29];
search.astar(nodes,start,end,grid);
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
