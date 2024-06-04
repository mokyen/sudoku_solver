#include "GridHelpers.h"
#include <gtest/gtest.h>

namespace GridHelpers {
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

} //namespace GridHelpers