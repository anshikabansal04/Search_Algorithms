#include "raylib.h"
#include "Grid.h"
#include "Search.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
void readMapFile(int& rows,int& cols,int& startRow,int& startCol, int& goalRow,int& goalCol,std::vector<std::pair<int,int>>& obstacles)
{
    std::ifstream file("../include/map.yaml");

    if (!file.is_open())
    {
        std::cout << "Failed to open map.yaml" << std::endl;
        return;
    }
    std::string line;
    bool readingStart = false;
    bool readingGoal = false;
    bool readingObstacles = false;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;

        if (line.find("rows:") != std::string::npos)
        {
            rows = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("cols:") != std::string::npos)
        {
            cols = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (line.find("start:") != std::string::npos)
        {
            readingStart = true;
            readingGoal = false;
        }
        else if (line.find("goal:") != std::string::npos)
        {
            readingGoal = true;
            readingStart = false;
        }
        else if (line.find("obstacles:") != std::string::npos)
       {
     readingObstacles = true;
     readingStart = false;
     readingGoal = false;
     }
        else if (readingStart && line.find("row:") != std::string::npos)
        {
            startRow = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (readingStart && line.find("col:") != std::string::npos)
        {
            startCol = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (readingGoal && line.find("row:") != std::string::npos)
        {
            goalRow = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (readingGoal && line.find("col:") != std::string::npos)
        {
            goalCol = std::stoi(line.substr(line.find(":") + 1));
        }
        else if (readingObstacles && line.find("-") != std::string::npos)
       {
         int row, col;

        sscanf(line.c_str(), " - [%d, %d]", &row, &col);

         obstacles.push_back({row, col});
}
    }

    file.close();
}
int main()
{
    Search search;
int rows = 0;
int cols = 0;

int startRow = 0;
int startCol = 0;

int goalRow = 0;
int goalCol = 0;
std::vector<std::pair<int, int>> obstacles;
readMapFile(rows, cols,startRow,startCol, goalRow, goalCol, obstacles
);
std::cout << "\nRows = " << rows << std::endl;
std::cout << "Cols = " << cols << std::endl;
std::cout << "Start = (" << startRow << "," << startCol << ")" << std::endl;
std::cout << "Goal = (" << goalRow << "," << goalCol << ")" << std::endl;
    // --- grid setup ---------------------------------------------------------

    constexpr int kCellSize = 28;

  Grid grid(rows, cols, kCellSize);

    // --- window -------------------------------------------------------------
    InitWindow(grid.pixelWidth(), grid.pixelHeight(), "Search Visualizer");
    SetTargetFPS(60);
std::vector<std::vector<Node>> nodes(
    rows,
    std::vector<Node>(cols)
);
for (int r = 0; r < rows; r++)
{
    for (int c = 0; c < cols; c++)
    {
        nodes[r][c].row = r;
        nodes[r][c].col = c;
    }
}

   for (auto obstacle : obstacles)
{
    int row = obstacle.first;
    int col = obstacle.second;

    nodes[row][col].obstacle = true;
    grid.set(row, col, BLACK);
    }

   Node* start = &nodes[startRow][startCol];
Node* end = &nodes[goalRow][goalCol];

    search.astar(nodes, start, end, grid);

    // --- render loop --------------------------------------------------------
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}