#include "PuzzleLoading.h"

namespace PuzzleLoading {

void loadPuzzle(Grid& grid, std::vector<LocationSolution> locationsToSet) {
    for (const auto& locationSolution : locationsToSet) {

        // std::cout << "x: " << x << "  y: " << y << " solution: " << solution << std::endl;;
            grid.setSolution(locationSolution);
            // grid.setSolution(1, 1, 3);
    }
}

} //namespace PuzzleLoading