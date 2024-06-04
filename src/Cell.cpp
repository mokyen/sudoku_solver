#include "Cell.h"
#include <ranges>

namespace {
std::set<int> createSequenceSet(int min, int max)
{
    std::set<int> ret;
    for (const int i : std::views::iota(min, max+1)) {
        ret.insert(i);
    }
    return ret;
}
}

Cell::Cell(int maxSolution) : 
m_candidates{createSequenceSet(1,maxSolution)}
{ }

std::set<int> Cell::getCandidates() const {
    return m_candidates;
}

void Cell::removeCandidate(int value) {
    m_candidates.erase(value);
}

std::optional<int> Cell::getSolution() const {
    return m_solution;
}

void Cell::setSolution(int value) {
    if (m_candidates.count(value) == 0) {
        throw std::invalid_argument( "Solution is not a candidate.");
    }
    else {
        m_solution = value;
        m_candidates.clear();
    }
}