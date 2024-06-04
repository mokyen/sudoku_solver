#include "Cell.h"
#include <vector>
#include <set>
#include <optional>
// #include <iostream>

class Grid
{
public:
    Grid(int dimension);

    std::set<int> getCandidates(int row, int column) const;
    void removeCandidate(int row, int column, int candidate);

    std::optional<int> getSolution(int row, int column) const;
    void setSolution(int row, int column, int value);

private:
    void performLocationValidCheck(int row, int column, int value = 1) const;
    std::vector<std::vector<Cell>> m_cells;
    int m_dimension;
    int m_blockSize;
};