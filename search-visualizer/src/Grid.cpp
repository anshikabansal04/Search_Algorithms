#include "Grid.h"

namespace {
const Color kTileColor = {245, 245, 245, 255};  // light grey fill
const Color kLineColor = {200, 200, 200, 255};  // grid lines
}  // namespace

Grid::Grid(int rows, int cols, int cellSize) // Constructor
    : rows_(rows),
      cols_(cols),
      cellSize_(cellSize),
      cells_(static_cast<size_t>(rows) * cols, kTileColor) {}


bool Grid::inBounds(int row, int col) const {
    return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

Color Grid::at(int row, int col) const {
    if (!inBounds(row, col)) return kTileColor;
    return cells_[static_cast<size_t>(row) * cols_ + col];
}

void Grid::set(int row, int col, Color color) {
    if (inBounds(row, col)) {
        cells_[static_cast<size_t>(row) * cols_ + col] = color;
    }
}

bool Grid::cellAtPixel(int x, int y, int& outRow, int& outCol) const {
    if (x < 0 || y < 0 || x >= pixelWidth() || y >= pixelHeight()) {
        return false;
    }
    outCol = x / cellSize_;
    outRow = y / cellSize_;
    return true;
}

void Grid::draw() const {
    // Fills
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            DrawRectangle(c * cellSize_, r * cellSize_, cellSize_, cellSize_,
                          at(r, c));
        }
    }
    // Grid lines
    for (int c = 0; c <= cols_; ++c) {
        DrawLine(c * cellSize_, 0, c * cellSize_, pixelHeight(), kLineColor);
    }
    for (int r = 0; r <= rows_; ++r) {
        DrawLine(0, r * cellSize_, pixelWidth(), r * cellSize_, kLineColor);
    }
}
