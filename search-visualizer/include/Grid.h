#pragma once

// A plain visual grid: it knows its size and how to draw itself. No algorithm
// logic lives here -- that's yours to add. Give a cell a colour via set()/at()
// if you later want to paint visited cells, walls, paths, etc.

#include <vector>

#include "raylib.h"

class Grid {
public:
   
    Grid(int rows, int cols, int cellSize); // Definations

    int rows() const { return rows_; }
    int cols() const { return cols_; }
    int cellSize() const { return cellSize_; }

    int pixelWidth() const { return cols_ * cellSize_; }
    int pixelHeight() const { return rows_ * cellSize_; }

    // Per-cell fill colour (defaults to a light tile). Read/write.
    Color at(int row, int col) const;
    void set(int row, int col, Color color);

    // Convert a screen pixel to the cell it lands on. Returns false if the
    // point is outside the grid.
    bool cellAtPixel(int x, int y, int& outRow, int& outCol) const;

    // Draw filled cells + grid lines.
    void draw() const;

private:
    /**
    * @brief This function checks if the given row and column indices are within the bounds of the grid.
    * 
    * @param row Number of rows
    * @param col Number of columns
    * @param cellSize size of cell

    * @return true 
    * @return false 
    */
    bool inBounds(int row, int col) const;

    int rows_;
    int cols_;
    int cellSize_;
    std::vector<Color> cells_;
};
