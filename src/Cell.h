#ifndef __CELL_H__
#define __CELL_H__

#include <optional>
#include <set>

class Cell {
public:
Cell(int maxSolution);
std::set<int> getCandidates() const;
void removeCandidate(int value);
std::optional<int> getSolution() const;
void setSolution(int value);

private:
std::optional<int> m_solution;
std::set<int> m_candidates;
};

#endif //#ifndef __CELL_H__