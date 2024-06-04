#include <optional>
#include <set>
#include <ranges>
#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include <cmath>

#define DISABLE_MOST_TESTING

constexpr std::set<int> createSequenceSet(int min, int max)
{
    std::set<int> ret;
    for (const int i : std::views::iota(min, max+1)) {
        ret.insert(i);
    }
    return ret;
}

class Cell {
public:
Cell(int maxSolution) : 
m_candidates{createSequenceSet(1,maxSolution)}
{ }
std::set<int> getCandidates() const {
    return m_candidates;
}
void removeCandidate(int value) {
    m_candidates.erase(value);
}
std::optional<int> getSolution() const {
    return m_solution;
}
void setSolution(int value) {
    if (m_candidates.count(value) == 0) {
        throw std::invalid_argument( "Solution is not a candidate.");
    }
    else {
        m_solution = value;
        m_candidates.clear();
    }
}
private:
std::optional<int> m_solution;
std::set<int> m_candidates;
};

class Cell_view {
public:
explicit Cell_view(const Cell& cell) : m_cell{cell}
{}
std::set<int> getCandidates() const {
    return m_cell.getCandidates();
}
std::optional<int> getSolution() const {
    return m_cell.getSolution();
}

//TODO decide if this should include X and Y

private:
const Cell& m_cell;
};

// int main()
// {
//   Cell c{9};
//     std::cout << "has solution: " << c.getSolution().has_value() << std::endl; 
//     c.removeCandidate(-1);
//     c.setSolution(1);
//     std::cout << "has solution: " << c.getSolution().has_value() << std::endl; 
    
//   auto d{c.getCandidates()};
    
    
//   for (auto it = d.begin(); it != d.end(); ++it)

//         std::cout << ' ' << *it;

    
//     std::cout << "set size: " << c.getCandidates().size() << std::endl;
//     std::set<int> m_candidates{1,2};
// }

#if !defined DISABLE_MOST_TESTING

TEST(CellTests, CreateCell)
{
    //Arrange, Act, and no real Assert
    Cell c{9};
}

TEST(CellTests, CellHasNoInitialSolution)
{
    //Arrange
    Cell c{9};
    //Act and Assert
    EXPECT_EQ(std::nullopt, c.getSolution());
}

TEST(CellTests, SetSolutionSetsSolution)
{
    //Arrange
    Cell c{9};
    //Act
    c.setSolution(7);
    //Assert
    EXPECT_EQ(7, c.getSolution());
}

TEST(CellTests, SetSolutionTooHighThrows)
{
    //Arrange
    Cell c{9};
    //Act and Assert
    EXPECT_THROW(c.setSolution(11), std::invalid_argument);
}

TEST(CellTests, SetSolutionTooLowThrows)
{
    //Arrange
    Cell c{9};
    //Act and Assert
    EXPECT_THROW(c.setSolution(-1), std::invalid_argument);
}

TEST(CellTests, CandidatesInitializedProperly)
{
    //Arrange
    Cell c{3};
    //Act and Assert
    EXPECT_EQ(c.getCandidates(), std::set({1,2,3}));
}

TEST(CellTests, RemoveCandidateRemoves)
{
    //Arrange
    Cell c{3};
    //Act
    c.removeCandidate(2);
    //Assert
    EXPECT_EQ(c.getCandidates(), std::set({1,3}));
}

TEST(CellTests, RemoveCandidateNotInListNoThrows)
{
    //Arrange
    Cell c{3};
    //Act and Assert
    EXPECT_NO_THROW(c.removeCandidate(9));
}

TEST(CellTests, SetSolutionClearsCandidates)
{
    //Arrange
    Cell c{3};
    //Act
    c.setSolution(2);
    //Assert
    EXPECT_EQ(c.getCandidates(), std::set<int>());
}

TEST(CellTests, RemoveCandidateAfterSetSolutionNoThrows)
{
    //Arrange
    Cell c{3};
    //Act
    c.setSolution(2);
    //Assert
    EXPECT_NO_THROW(c.removeCandidate(9));
}

TEST(CellTests, SetSolutionAfterSolutionSetThrows)
{
    //Arrange
    Cell c{3};
    //Act
    c.setSolution(2);
    //Assert
    EXPECT_THROW(c.setSolution(1), std::invalid_argument);
}

TEST(Cell_view_tests, CanCreate)
{
    //Arrange
    Cell c{3};
    //Act and Assert
    Cell_view cv(c);
}

TEST(Cell_view_tests, CanGetCandidates)
{
    //Arrange
    Cell c{3};
    Cell_view cv(c);
    //Act and Assert
    EXPECT_EQ(cv.getCandidates(), std::set({1,2,3}));
}

TEST(Cell_view_tests, RemoveCandidateViewUpdates)
{
    //Arrange
    Cell c{3};
    Cell_view cv(c);
    //Act
    c.removeCandidate(2);
    //Assert
    EXPECT_EQ(cv.getCandidates(), std::set({1,3}));
}

TEST(Cell_view_tests, SetSolutionViewUpdates)
{
    //Arrange
    Cell c{3};
    Cell_view cv(c);
    //Act
    c.setSolution(2);
    //Assert
    EXPECT_EQ(cv.getCandidates(), std::set<int>());
    EXPECT_EQ(cv.getSolution(), 2);
}
#endif

//======================================================
#include <string_view>

template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

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

#if !defined DISABLE_MOST_TESTING
TEST(FreeFunctionTests, GetLocationsInRow)
{
    //Arrange
    auto expectedLocations = std::vector<std::pair<int,int>>({{1,1}, {1,2}, {1,3}, {1,4}});
    //Act, and Assert
    EXPECT_EQ(getLocationsInRow(4, 1), expectedLocations);
}

TEST(FreeFunctionTests, GetLocationsInCol)
{
    //Arrange
    auto expectedLocations = std::vector<std::pair<int,int>>({{1,2}, {2,2}, {3,2}, {4,2}});
    //Act, and Assert
    EXPECT_EQ(getLocationsInCol(4, 2), expectedLocations);
}

TEST(FreeFunctionTests, GetLocationsInBlock)
{
    //Arrange
    auto expectedLocations = std::vector<std::pair<int,int>>({{3,1}, {3,2}, {4,1}, {4,2}});
    //Act, and Assert
    EXPECT_EQ(getLocationsInBlock(4, 3, 1), expectedLocations);
}
#endif //defined DISABLE_MOST_TESTING

class Grid
{
public:
    Grid(int dimension) 
    {
        Cell initialCell(dimension);

        std::vector<std::vector<Cell>> cellsInitializer(
            dimension,
            std::vector<Cell>(dimension, initialCell));

        m_cells = cellsInitializer;

        auto sqrtDimension = static_cast<int>(std::sqrt(dimension));

        if ((sqrtDimension*sqrtDimension) != dimension)
        {
            throw std::invalid_argument( "Grid dimension is not a square of an integer value.");
        }
        else {
            m_blockSize = sqrtDimension;
        }
    }

    std::set<int> getCandidates(int row, int column) {return m_cells[row - 1][column - 1].getCandidates();}

    void removeCandidate(int row, int column, int candidate) {
        auto [r, c] = convertUserCoordinatesToInternal(row, column);
        m_cells[r][c].removeCandidate(candidate);
    }

    std::optional<int> getSolution(int row, int column) {
        auto [r, c] = convertUserCoordinatesToInternal(row, column);
        return m_cells[r][c].getSolution();
    }

    void setSolution(int row, int column, int value) {

        int dimension{static_cast<int>(m_cells.size())};

        if ((row > dimension) || (column > dimension) || (value > dimension))
        {
            std::string error("row: " + std::to_string(row)
                                + "  col: "+ std::to_string(column)
                                + "  value: "+ std::to_string(value)
                                + "  dimension: "+ std::to_string(dimension)
            );

            throw std::invalid_argument( "Dimension not permitted. " + error);
        }

        auto [r, c] = convertUserCoordinatesToInternal(row, column);

        // std::cout << "R.C: " << r << "." << c << std::endl;

        m_cells[r][c].setSolution(value);

        auto rowlocationsToRemoveSolution{getLocationsInRow(dimension, row)};
        auto colLocationsToRemoveSolution{getLocationsInCol(dimension, column)};
        auto blockLocationsToRemoveSolution{getLocationsInBlock(dimension, row, column)};

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

private:
    std::vector<std::vector<Cell>> m_cells;
    int m_blockSize;
};

#if !defined DISABLE_MOST_TESTING
TEST(GridTests, CanCreateGrid)
{
    Grid a{9};
}

TEST(GridTests, GetInitialCandidatesAtLocation)
{
    //Arrange
    Grid uut{1};
    //Act and Assert
    EXPECT_EQ(uut.getCandidates(1,1), std::set({1}));
}

TEST(GridTests, GetInitialCandidatesAtLocationDifferentSize)
{
    //Arrange
    Grid uut{4};
    //Act and Assert
    EXPECT_EQ(uut.getCandidates(1,1), std::set({1,2,3,4}));
}

TEST(GridTests, InitializeGridWithNonSquareThrows)
{
    //Arrange
    auto test = [](int size){ Grid uut{size};};
    //Act, and Assert 
    EXPECT_THROW(test(2), std::invalid_argument);
    EXPECT_THROW(test(5), std::invalid_argument);
    EXPECT_THROW(test(7), std::invalid_argument);
    EXPECT_THROW(test(10), std::invalid_argument);
}

TEST(GridTests, RemoveCandidateAtLocation)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.removeCandidate(1,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(1,1), std::set({1,3,4}));
}

TEST(GridTests, RemoveCandidatesAtDifferentLocations)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.removeCandidate(1,1,2);
    uut.removeCandidate(1,2,3);
    //Assert
    EXPECT_EQ(uut.getCandidates(1,1), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(1,2), std::set({1,2,4}));
}

TEST(GridTests, RemoveCandidatesBeyondSizeThrows)
{
    //Arrange
    Grid uut{4};
    //Act and Assert
    EXPECT_ANY_THROW(uut.removeCandidate(6,1,2));
    EXPECT_ANY_THROW(uut.removeCandidate(11,1,2));
}

TEST(GridTests, GridIsOneIndexed)
{
    //Arrange
    Grid uut{4};
    //Act and Assert
    EXPECT_ANY_THROW(uut.removeCandidate(0,0,2));
}

TEST(GridTests, SolutionInitiallyNullopt)
{
    //Arrange
    Grid uut{4};
    //Act and Assert
    EXPECT_EQ(std::nullopt, uut.getSolution(1,2));
}

TEST(GridTests, SetSolutionSetsSolution)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(1,1,2);
    //Assert
    EXPECT_EQ(uut.getSolution(1,1), 2);
}
#endif
TEST(GridTests, SetSolutionRemovesCandidatesFromRow)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(1,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(1,2), std::set({1,3,4}));
}

TEST(GridTests, SetSolutionRemovesCandidatesFromColumn)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(1,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(2,1), std::set({1,3,4}));
}

TEST(GridTests, SetSolutionRemovesCandidatesFromBlock)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(1,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(2,2), std::set({1,3,4}));
}

TEST(GridTests, SetSolutionDoesNotRemoveFromOutsideRowColumnBlock)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(1,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(2,3), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(2,4), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(3,2), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(3,3), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(3,4), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(4,2), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(4,3), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(4,4), std::set({1,2,3,4}));
}

TEST(GridTests, SetSolutionRemovesAllCandidatesFromCell2)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(3,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(3,1), std::set<int>());
}

TEST(GridTests, SetSolutionRemovesCandidatesFromCol2)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(3,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(1,1), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(2,1), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(4,1), std::set({1,3,4}));
}

TEST(GridTests, SetSolutionRemovesCandidatesFromRow2)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(3,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(3,2), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(3,3), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(3,4), std::set({1,3,4}));
}

TEST(GridTests, SetSolutionRemovesCandidatesFromBlock2)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(3,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(3,2), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(4,1), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(4,2), std::set({1,3,4}));
}

TEST(GridTests, SetSolutionDoesNotRemoveFromOutsideRowColumnBlock2)
{
    //Arrange
    Grid uut{4};
    //Act
    uut.setSolution(3,1,2);
    //Assert
    EXPECT_EQ(uut.getCandidates(3,2), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(3,3), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(3,4), std::set({1,3,4}));
    EXPECT_EQ(uut.getCandidates(1,2), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(1,3), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(1,4), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(2,2), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(2,3), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(2,4), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(4,3), std::set({1,2,3,4}));
    EXPECT_EQ(uut.getCandidates(4,4), std::set({1,2,3,4}));
}
// #endif

void loadPuzzle(Grid& grid, std::vector<std::tuple<int,int,int>> cellsToSet) {
    for (auto [r, c, solution] : cellsToSet) {
        // std::cout << "x: " << x << "  y: " << y << " solution: " << solution << std::endl;;
            grid.setSolution(r, c, solution);
            // grid.setSolution(1, 1, 3);
    }
}

TEST(PuzzleLoaderTests, CanCreate)
{
    //Arrange
    Grid g{4};
    // g.setSolution(2, 2, 3);
    //Act
    loadPuzzle(g, {{1,1,4}, {3,1,2}});
    //Assert
    EXPECT_EQ(g.getSolution(1,1), 4);
    EXPECT_EQ(g.getSolution(3,1), 2);

    EXPECT_EQ(g.getCandidates(1,1), std::set<int>());
    EXPECT_EQ(g.getCandidates(1,2), std::set({1,2,3}));
    EXPECT_EQ(g.getCandidates(1,3), std::set({1,2,3}));
    EXPECT_EQ(g.getCandidates(1,4), std::set({1,2,3}));
    EXPECT_EQ(g.getCandidates(2,1), std::set({1,3}));
    EXPECT_EQ(g.getCandidates(2,2), std::set({1,2,3}));
    EXPECT_EQ(g.getCandidates(2,3), std::set({1,2,3,4}));
    EXPECT_EQ(g.getCandidates(2,4), std::set({1,2,3,4}));
    EXPECT_EQ(g.getCandidates(3,1), std::set<int>());
    EXPECT_EQ(g.getCandidates(3,2), std::set({1,3,4}));
    EXPECT_EQ(g.getCandidates(3,3), std::set({1,3,4}));
    EXPECT_EQ(g.getCandidates(3,4), std::set({1,3,4}));
    EXPECT_EQ(g.getCandidates(4,1), std::set({1,3}));
    EXPECT_EQ(g.getCandidates(4,2), std::set({1,3,4}));
    EXPECT_EQ(g.getCandidates(4,3), std::set({1,2,3,4}));
    EXPECT_EQ(g.getCandidates(4,4), std::set({1,2,3,4}));
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}