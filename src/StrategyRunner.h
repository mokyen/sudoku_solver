#ifndef __STRATEGY_RUNNER_H__
#define __STRATEGY_RUNNER_H__

#include "Grid.h"
#include "LocationSolution.h"
#include <functional>
#include <vector>


using Strategy = std::function<std::vector<LocationSolution>(const Grid&)>;

void runStrategies(Grid& grid, const std::vector<Strategy>& strategies);
bool runSingleStrategy(Grid& grid, const Strategy& strategy);


#endif //__STRATEGY_RUNNER_H__