#include <gtest/gtest.h>
#include "Cell.h"

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