#include <gtest/gtest.h>
#include "CellView.h"

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