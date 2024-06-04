#include "GridHelpers.h"
#include <cmath>

namespace GridHelpers {

std::pair<int, int> convertUserCoordinatesToInternal(int row, int column)
{
    int r{row - 1};
    int c{column - 1};

    return {r,c};
}

std::pair<int, int> convertInternalCoordinatesToUser(int row, int column)
{
    int r{row + 1};
    int c{column + 1};

    return {r,c};
}

int computeBlockSize(int dimension) {
    return static_cast<int>(std::sqrt(dimension));
}

std::vector<std::pair<int,int>> getLocationsInRow(int dimension, int row)
{
    std::vector<std::pair<int,int>> ret(dimension);

    int i{1};
    for (auto& location : ret)
    {
        location = std::make_pair(row,i);
        i++;
    }

    return ret;
}

std::vector<std::pair<int,int>> getLocationsInCol(int dimension, int col)
{
    std::vector<std::pair<int,int>> ret(dimension);

    int i{1};
    for (auto& location : ret)
    {
        location = std::make_pair(i, col);
        i++;
    }

    return ret;
}

//TODO consider rewriting this function to be safer
std::vector<std::pair<int,int>> getLocationsInBlock(int dimension, int row, int col)
{
    std::vector<std::pair<int,int>> ret(dimension);
    auto [r, c] = convertUserCoordinatesToInternal(row, col);
    auto blockSize{computeBlockSize(dimension)};

    int blockRowStart{(r / blockSize) * blockSize};
    int blockRowEnd{blockRowStart + blockSize};

    int blockColStart{(c / blockSize) * blockSize};
    int blockColEnd{blockColStart + blockSize};

    int k{0};
    for (int i = blockRowStart; i < blockRowEnd; i++) {
        for (int j = blockColStart; j < blockColEnd; j++) {
            ret[k] = convertInternalCoordinatesToUser(i,j);
            k++;
        }
    }

    return ret;
}

} //namespace GridHelpers