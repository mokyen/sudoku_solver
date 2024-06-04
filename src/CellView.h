#ifndef __CELL_VIEW_H__
#define __CELL_VIEW_H__

#include "Cell.h"
#include <set>
#include <optional>

class Cell_view {
public:
explicit Cell_view(const Cell& cell);
std::set<int> getCandidates() const;
std::optional<int> getSolution() const;

//TODO decide if this should include X and Y

private:
const Cell& m_cell;
};

#endif // __CELL_VIEW_H__