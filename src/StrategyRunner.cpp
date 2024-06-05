#include "StrategyRunner.h"

void runStrategies(Grid& grid, const std::vector<Strategy>& strategies)
{
    auto wereAnyChangesMade{false};

    do {
        for (const auto& strategy : strategies) {
            auto didStrategyMakeChange = runSingleStrategy(grid, strategy);
            if (didStrategyMakeChange) {
                wereAnyChangesMade = true;
            }
        }
    } while (wereAnyChangesMade);

}

bool runSingleStrategy(Grid& grid, const Strategy& strategy) {
    
    // return strategy(grid);
    auto wasAnyChangeMade{false};
    std::vector<LocationSolution> locSolsToSet;

    do {
        locSolsToSet = strategy(grid);
        if (!locSolsToSet.empty()) {
            wasAnyChangeMade = true;
        }
        for (const auto& loc : locSolsToSet) {
            grid.setSolution(loc);
        }
    } while (!locSolsToSet.empty());


    return wasAnyChangeMade;
}