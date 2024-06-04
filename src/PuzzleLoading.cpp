#include "PuzzleLoading.h"

namespace PuzzleLoading {

void loadPuzzle(Grid& grid, std::vector<std::tuple<int,int,int>> cellsToSet) {
    for (auto [r, c, solution] : cellsToSet) {
        // std::cout << "x: " << x << "  y: " << y << " solution: " << solution << std::endl;;
            grid.setSolution(r, c, solution);
            // grid.setSolution(1, 1, 3);
    }
}

} //namespace PuzzleLoading