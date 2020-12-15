#ifndef PROBLEMS_HPP_INCLUDED
#define PROBLEMS_HPP_INCLUDED

#define dynamic_size_container_t void
dynamic_size_container_t decompose_into_sums(uint16_t number) {}

bool decide_if_sparse_is_better(int[][] table) {}   // a zero means that the cell should be treated as NULL in SQL

#define series_t void*
int compare_series(series_t A, series_t B) {}   // <e.g.> n < n * logn < n^2; what about n^(logn) vs the polynomials and the exponentials [such as 2^(n/3)] ?



#endif // PROBLEMS_HPP_INCLUDED
