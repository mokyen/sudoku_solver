#include <gtest/gtest.h>
#include "Strategies.h"

TEST(SingleCandidateStrategiesTests, CanCreate) {
    //Arrange, Act, Assert
    auto s{Strategies::getSingleCandidateStrategy()};
}

TEST(SingleCandidateStrategiesTests, CanCreate3) {
    //Arrange
    auto s{Strategies::getSingleCandidateStrategy()};
    Grid g{4};
      //Load puzzle
    g.removeCandidate(1,1,2);
    g.removeCandidate(1,1,3);
    g.removeCandidate(1,1,4);

    std::vector<LocationSolution> expectedLocSols{{1,1,1}};
    //Act
    auto locationSolutions = s(g);
    //Assert
    EXPECT_EQ(locationSolutions, expectedLocSols);
}

TEST(SingleCandidateStrategiesTests, CanCreate4) {
    //Arrange
    auto s{Strategies::getSingleCandidateStrategy()};
    Grid g{4};
      //Load puzzle
    g.setSolution(1,1,1);
    g.setSolution(1,2,2);
    g.setSolution(2,1,3);

    std::vector<LocationSolution> expectedLocSols{{2,2,4}};
    //Act
    auto locationSolutions = s(g);
    //Assert
    EXPECT_EQ(locationSolutions, expectedLocSols);
}

TEST(SingleCandidateStrategiesTests, CanCreate2) {
    //Arrange
    auto s{Strategies::getSingleCandidateStrategy()};
    Grid g{4};
      //Load puzzle
    g.setSolution(1,1,4);
    g.setSolution(1,3,1);
    g.setSolution(2,2,2);
    g.setSolution(3,3,3);
    g.setSolution(4,4,1);

    Grid expectedGrid{g};
    expectedGrid.setSolution(1,2,3);
    expectedGrid.setSolution(1,4,2);
    expectedGrid.setSolution(2,1,1);
    expectedGrid.setSolution(2,3,4);
    expectedGrid.setSolution(2,4,3);
    expectedGrid.setSolution(3,1,2);
    expectedGrid.setSolution(3,2,1);
    expectedGrid.setSolution(3,4,4);
    expectedGrid.setSolution(4,1,3);
    expectedGrid.setSolution(4,2,4);
    expectedGrid.setSolution(4,3,2);
    //Act
    for (int i = 0; i < 10; i++) {
        auto locationSolutions = s(g);
        for (const auto& ls : locationSolutions) {
            g.setSolution(ls);
        }
        std::cout << "size: " << locationSolutions.size() << std::endl;
    }
    //Assert
    EXPECT_EQ(g, expectedGrid);
}