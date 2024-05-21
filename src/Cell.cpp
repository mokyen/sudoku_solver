#include <optional>
#include <set>
#include <ranges>
#include <iostream>
#include <stdexcept>

constexpr std::set<int> createSequenceSet(int min, int max)
{
    std::set<int> ret;
    for (const int i : std::views::iota(min, max+1)) {
        ret.insert(i);
    }
    return ret;
}

class Cell {
public:
Cell(int maxSolution) : 
m_maxSolution{maxSolution},
m_candidates{createSequenceSet(1,maxSolution)}
{ }
std::set<int> getCandidates() const {
    return m_candidates;
}
void removeCandidate(int value) {
    m_candidates.erase(value);
}
std::optional<int> getSolution() const {
    return m_solution;
}
void setSolution(int value) {
    if (value > m_maxSolution) {
        throw std::invalid_argument( "Solution exceeds max value.");
    }
    else if (m_candidates.count(value) == 0) {
        throw std::invalid_argument( "Solution is not a candidate.");
    }
    else {
        m_solution = value;
        m_candidates = std::set<int>({value});
    }
}
private:
int m_maxSolution;
std::optional<int> m_solution;
std::set<int> m_candidates;
};

int main()
{
  Cell c{9};
    std::cout << "has solution: " << c.getSolution().has_value() << std::endl; 
    c.removeCandidate(-1);
    c.setSolution(1);
    std::cout << "has solution: " << c.getSolution().has_value() << std::endl; 
    
  auto d{c.getCandidates()};
    
    
  for (auto it = d.begin(); it != d.end(); ++it)

        std::cout << ' ' << *it;

    
    std::cout << "set size: " << c.getCandidates().size() << std::endl;
    std::set<int> m_candidates{1,2};
}