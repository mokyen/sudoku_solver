#ifndef __GRID_H__
#define __GRID_H__

#include "Cell.h"
#include <vector>
#include <set>
#include <optional>
// #include <iostream>
#include "LocationSolution.h"

class Grid
{
public:
    Grid(int dimension);
    
    int getDimension() const;

    std::set<int> getCandidates(int row, int column) const;
    void removeCandidate(int row, int column, int candidate);

    std::optional<int> getSolution(int row, int column) const;
    void setSolution(int row, int column, int value);
    void setSolution(LocationSolution locationSolution);

private:
    void performLocationValidCheck(int row, int column, int value = 1) const;
    std::vector<std::vector<Cell>> m_cells;
    int m_dimension;
    int m_blockSize;
};



bool operator==(const Grid &lhs, const Grid &rhs);

#endif //__GRID_H__