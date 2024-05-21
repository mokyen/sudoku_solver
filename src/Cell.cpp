//https://godbolt.org/z/TffcxEvaj

#include <optional>
#include <set>
#include <ranges>
#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include <cmath>

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

        // std::cout << "Size: " << cellsInitializer.size() << std::endl;


    }

    std::set<int> getCandidates(int row, int column) {return m_cells[row - 1][column - 1].getCandidates();}

    void removeCandidate(int row, int column, int candidate) {
        m_cells[row -1][column -1].removeCandidate(candidate);
    }

    std::optional<int> getSolution(int row, int column) {
        return m_cells[row - 1][column - 1].getSolution();
    }

    void setSolution(int row, int column, int value) {

        //Internal variables
        int c = column - 1;
        int r = row - 1;

        m_cells[r][c].setSolution(value);

        //Remove candidates from row
        for (auto& cell : m_cells[r]) {
                cell.removeCandidate(value);
        }
        //Remove candidates from column
        for (auto& cellRow : m_cells) {
                cellRow[c].removeCandidate(value);
        }

        int blockRowStart{(r % m_blockSize) * m_blockSize};
        int blockRowEnd{blockRowStart + m_blockSize};

        int blockColStart{(c % m_blockSize) * m_blockSize};
        int blockColEnd{blockColStart + m_blockSize - 1};

        for (int i = blockRowStart; i < blockRowEnd; i++) {
            for (int j = blockColStart; j < blockColEnd; j++) {
                m_cells[i][j].removeCandidate(value);
            }
        }

        // int blockSize{m_cells.size()}

    }

private:
    std::vector<std::vector<Cell>> m_cells;
    int m_blockSize;
};

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




int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}