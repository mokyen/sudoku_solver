#include "CellView.h"

Cell_view::Cell_view(const Cell& cell) : m_cell{cell}
{}

std::set<int> Cell_view::getCandidates() const {
    return m_cell.getCandidates();
}

std::optional<int> Cell_view::getSolution() const {
    return m_cell.getSolution();
}