#include "Grid.h"
#include "GridHelpers.h"
#include <string>
#include <cmath>
#include <iostream>
#include <stdexcept>

Grid::Grid(int dimension) : m_dimension{dimension} {
    Cell initialCell(m_dimension);

    std::vector<std::vector<Cell>> cellsInitializer(
        m_dimension,
        std::vector<Cell>(m_dimension, initialCell));

    m_cells = cellsInitializer;

    auto sqrtDimension = static_cast<int>(std::sqrt(m_dimension));

    if ((sqrtDimension*sqrtDimension) != m_dimension)
    {
        throw std::invalid_argument( "Grid dimension is not a square of an integer value.");
    }
    else {
        m_blockSize = sqrtDimension;
    }
}

int Grid::getDimension() const {
    return m_dimension;
}

std::set<int> Grid::getCandidates(int row, int column) const {
    performLocationValidCheck(row, column);
    return m_cells[row - 1][column - 1].getCandidates();
}

void Grid::removeCandidate(int row, int column, int candidate) {
    performLocationValidCheck(row, column);
    auto [r, c] = GridHelpers::convertUserCoordinatesToInternal(row, column);
    m_cells[r][c].removeCandidate(candidate);
}

std::optional<int> Grid::getSolution(int row, int column) const {
    performLocationValidCheck(row, column);
    auto [r, c] = GridHelpers::convertUserCoordinatesToInternal(row, column);
    return m_cells[r][c].getSolution();
}

void Grid::setSolution(int row, int column, int value) {

    performLocationValidCheck(row, column, value);

    auto [r, c] = GridHelpers::convertUserCoordinatesToInternal(row, column);

    // std::cout << "R.C: " << r << "." << c << std::endl;

    m_cells[r][c].setSolution(value);

    auto rowlocationsToRemoveSolution{GridHelpers::getLocationsInRow(m_dimension, row)};
    auto colLocationsToRemoveSolution{GridHelpers::getLocationsInCol(m_dimension, column)};
    auto blockLocationsToRemoveSolution{GridHelpers::getLocationsInBlock(m_dimension, row, column)};

    auto allLocationsToRemoveSolution{rowlocationsToRemoveSolution};
    allLocationsToRemoveSolution.insert(allLocationsToRemoveSolution.end(),
                                        colLocationsToRemoveSolution.begin(),
                                        colLocationsToRemoveSolution.end());
    allLocationsToRemoveSolution.insert(allLocationsToRemoveSolution.end(),
                                        blockLocationsToRemoveSolution.begin(),
                                        blockLocationsToRemoveSolution.end());

    for (const auto [r_, c_] : allLocationsToRemoveSolution)
    {
        // std::cout << "R_.C_: " << r_ << "." << c_ << std::endl;
        // auto [row_, col_] = convertInternalCoordinatesToUser(r_, c_);
        removeCandidate(r_, c_, value);
    }
}

void Grid:: setSolution(LocationSolution locationSolution)
{
    this->setSolution(locationSolution.row, locationSolution.col, locationSolution.solution);
}

void Grid::performLocationValidCheck(int row, int column, int value) const {

    if (((row > m_dimension) || (column > m_dimension) || (value > m_dimension)) ||
        ((row < 1) || (column < 1) || (value < 1 )))
    {
        std::string error("row: " + std::to_string(row)
                            + "  col: "+ std::to_string(column)
                            + "  value: "+ std::to_string(value)
                            + "  dimension: "+ std::to_string(m_dimension)
        );

        throw std::invalid_argument( "Dimension not permitted. " + error);
    }
}

bool operator==(const Grid &lhs, const Grid &rhs) {
    bool match{true};
    auto dimension{lhs.getDimension()};
    for (int i = 1; i <= dimension; i++) {
        for (int j = 1; j <= dimension; j++) {
            if (lhs.getSolution(i, j) != rhs.getSolution(i, j)) {
                match = false;
                std::cout << "location " << i << "." << j <<
                    " doesn't match. Solutions are " << lhs.getSolution(i, j).value_or(-1) << " and " <<  rhs.getSolution(i, j).value_or(-1) << std::endl;
                break;
            }
            if (lhs.getCandidates(i, j) != rhs.getCandidates(i, j)) {
                match = false;
                break;
            }
        }
        if (!match) {
            break;
        }
    }
    return match;
}
