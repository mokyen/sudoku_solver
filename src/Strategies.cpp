#include "Strategies.h"

namespace Strategies {

Strategy getSingleCandidateStrategy() {

    auto singleCandidateStrategy = [](const Grid& g) -> std::vector<LocationSolution> { 
        auto dimension{g.getDimension()};
        std::vector<LocationSolution> ret;
        for (int i = 1; i <= dimension; i++) {
            for (int j = 1; j <= dimension; j++) {
                if (g.getCandidates(i,j).size() == 1) {
                    int solution{*(g.getCandidates(i,j).begin())};
                    ret.push_back({i,j, solution});
                }
            }
        }
        return ret;
    };

    return singleCandidateStrategy;
    // return [](const Grid& g) -> std::vector<LocationSolution> { return {};};
}

} //namespace Strategies
