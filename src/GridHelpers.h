#ifndef __GRID_HELPERS_H__
#define __GRID_HELPERS_H__

#include <tuple>
#include <vector>

namespace GridHelpers {

std::pair<int, int> convertUserCoordinatesToInternal(int row, int column);
std::pair<int, int> convertInternalCoordinatesToUser(int row, int column);
int computeBlockSize(int dimension);
std::vector<std::pair<int,int>> getLocationsInRow(int dimension, int row);
std::vector<std::pair<int,int>> getLocationsInCol(int dimension, int col);
//TODO consider rewriting this function to be safer
std::vector<std::pair<int,int>> getLocationsInBlock(int dimension, int row, int col);

} //namespace GridHelpers

#endif //__GRID_HELPERS_H__