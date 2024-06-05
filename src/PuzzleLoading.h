#ifndef __PUZZLE_LOADING_H__
#define __PUZZLE_LOADING_H__

#include <vector>
#include "Grid.h"
#include "LocationSolution.h"

namespace PuzzleLoading {

void loadPuzzle(Grid& grid, std::vector<LocationSolution> cellsToSet);

} //namespace PuzzleLoading

#endif //__PUZZLE_LOADING_H__