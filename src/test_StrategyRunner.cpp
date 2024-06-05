#include <gtest/gtest.h>
#include "StrategyRunner.h"
#include "Grid.h"
#include "LocationSolution.h"

// TEST(StrategyRunnerTests, CanCall)
// {
//     //Arrange
//     Grid g{4};
//     Strategy s = [](const Grid& grid) -> std::vector<LocationSolution> {
//         LocationSolution ret;
//         ret.row = 1;
//         ret.col = 1;
//         ret.solution = 1;
//         return {ret};
//     };
//     //Act and Assert
//     runStrategies(g, {s});
// }

TEST(StrategyRunnerTests, CanCall2)
{
    //Arrange
    Grid g{4};
    Strategy s = [](const Grid& grid) -> std::vector<LocationSolution> {
            return {};
    };
    //Act and Assert
    runStrategies(g, {s});
}

TEST(StrategyRunnerTests, StrategyReturnsEmptyCallReturnsFalse)
{
    //Arrange
    Grid g{4};
    Strategy s = [](const Grid& grid) -> std::vector<LocationSolution> {
            return {};
    };
    //Act and Assert
    EXPECT_FALSE(runSingleStrategy(g, s));
}

TEST(StrategyRunnerTests, CanCallSingleStrategyRun)
{
    //Arrange
    Grid g{4};
    bool hasRun{false};
    Strategy s = [&hasRun](const Grid& grid) -> std::vector<LocationSolution> {
        if (hasRun) {
            return {};
        }
        else {
            LocationSolution ret;
            ret.row = 1;
            ret.col = 1;
            ret.solution = 1;
            hasRun = true;
            return {ret};
        }
    };
    //Act and Assert
    auto ret = runSingleStrategy(g, s);
}

/*
TEST(StrategyRunnerTests, SingleStrategyWithNoReturnsRunsOnce)
{
    //Arrange
    Grid g{4};
    int spyRunCount;

    Strategy s = [&spyRunCount](const Grid& grid) -> std::vector<LocationSolution> {
        spyRunCount++;
        return std::vector<LocationSolution>();
    };
    //Act
    auto ret = runSingleStrategy(g, s);
    //Assert
    EXPECT_TRUE(ret.size() == 0);
    EXPECT_EQ(spyRunCount, 1);
}

*/


// TEST(StrategyRunnerTests, SingleStrategyWithNoReturnsRunsOnce2)
// {
//     //Arrange
//     Grid g{4};
//     int spyRunCount;
//     constexpr int maxRunCount{4};

//     LocationSolution dummyLocation;
//     dummyLocation.row = 1;
//     dummyLocation.col = 1;
//     dummyLocation.solution = 1;

//     Strategy s = [&spyRunCount, maxRunCount, dummyLocation](const Grid& grid) -> std::vector<LocationSolution> {
//         spyRunCount++;
//         return std::vector<LocationSolution>();
//     };
//     //Act and Assert
//     auto ret = runSingleStrategy(g, s);
//     //Assert
//     EXPECT_TRUE(ret.size() == 0);
//     EXPECT_EQ(spyRunCount, 1);
// }



TEST(StrategyRunnerTests, SingleStrategyReturns)
{
    //Arrange
    Grid g{4};
    int spyRunCount{0};
    constexpr int maxRunCount{4};

    Strategy s = [&spyRunCount, maxRunCount](const Grid& grid) -> std::vector<LocationSolution> {
        
        if (spyRunCount < maxRunCount)
        {
            spyRunCount++;
            LocationSolution dummyLocation;
            dummyLocation.row = spyRunCount;
            dummyLocation.col = 1;
            dummyLocation.solution = spyRunCount;

            return {dummyLocation};
        }
        else
        {
            return std::vector<LocationSolution>();
        }
    };
    std::vector<LocationSolution> expectedLocSol{LocationSolution(1,1,1),
                                                LocationSolution(2,1,1),
                                                LocationSolution(3,1,1),
                                                LocationSolution(4,1,1)};
    //Act
    auto ret = runSingleStrategy(g, s);

    //Assert
    EXPECT_TRUE(ret);
    EXPECT_EQ(spyRunCount, maxRunCount);
}
