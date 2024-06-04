#include <gtest/gtest.h>
#include "PuzzleLoading.h"

TEST(PuzzleLoaderTests, CanCreate)
{
    //Arrange
    Grid g{4};
    //Act
    PuzzleLoading::loadPuzzle(g, {{1,1,4}, {3,1,2}});
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