#include <gtest/gtest.h>
#include "Grid.h"

// TEST(GridTests, CanCreateGrid)
// {
//     Grid a{9};
// }

// TEST(GridTests, GetInitialCandidatesAtLocation)
// {
//     //Arrange
//     Grid uut{1};
//     //Act and Assert
//     EXPECT_EQ(uut.getCandidates(1,1), std::set({1}));
// }

// TEST(GridTests, GetInitialCandidatesAtLocationDifferentSize)
// {
//     //Arrange
//     Grid uut{4};
//     //Act and Assert
//     EXPECT_EQ(uut.getCandidates(1,1), std::set({1,2,3,4}));
// }

// TEST(GridTests, InitializeGridWithNonSquareThrows)
// {
//     //Arrange
//     auto test = [](int size){ Grid uut{size};};
//     //Act, and Assert 
//     EXPECT_THROW(test(2), std::invalid_argument);
//     EXPECT_THROW(test(5), std::invalid_argument);
//     EXPECT_THROW(test(7), std::invalid_argument);
//     EXPECT_THROW(test(10), std::invalid_argument);
// }

// TEST(GridTests, RemoveCandidateAtLocation)
// {
//     //Arrange
//     Grid uut{4};
//     //Act
//     uut.removeCandidate(1,1,2);
//     //Assert
//     EXPECT_EQ(uut.getCandidates(1,1), std::set({1,3,4}));
// }

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

TEST(GridTests, SetLocationSolutionSetsSolution)
{
    //Arrange
    Grid uut{4};
    LocationSolution ls;
    ls.row = 1;
    ls.col = 1;
    ls.solution = 2;
    //Act
    uut.setSolution(ls);
    //Assert
    EXPECT_EQ(uut.getSolution(1,1), 2);
}