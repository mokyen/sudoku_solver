#ifndef __LOCATION_SOLUTION_H__
#define __LOCATION_SOLUTION_H__

struct LocationSolution {
    int row;
    int col;
    int solution;
};

inline bool operator==(const LocationSolution &lhs, const LocationSolution &rhs) {
    return (lhs.row == rhs.row) && (lhs.col == rhs.col) && (lhs.solution == rhs.solution) ;}


#endif //__LOCATION_SOLUTION_H__