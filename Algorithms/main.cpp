#include <iostream>
#include <string>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

#include "BinarySearch.hpp"
#include "FibonnaciSearch.hpp"
#include "Sort.hpp"
#include "CountProblems.hpp"
#include "Formatting.hpp"

#include "Linux.hpp"
#include "Bitmap.hpp"
#include "Blur.hpp"
#include "Polynomial.hpp"
#include "FileIO.hpp"
#include "CollectionTypes.hpp"

int main() {
// test binary search
    int array[] {-2, 7, 84, 10, -83, 123, -983, 73, -0, -2};
    selection_sort(array, sizeof(array) / sizeof(int), compare_int, true);
    std::cout << binary_search_v1(array, sizeof(array) / sizeof(int), 0) << "\n";
    std::cout << binary_search_v2(array, sizeof(array) / sizeof(int), -2) << "\n";

// test formatting
    std::cout << normalized_radix10(fibonacci(32), 6) << "\n";

    uint32_t bla = 124141241124141241;
    std::cout << bitstring(bla) << "\n";
    uint64_t cra = 124141241124141241124141241124141241;
    std::cout << bitstring(cra) << "\n";
    std::cout << formatted_byte_size(fibonacci(32) * sizeof(uint32_t)) << "\n";
//    std::cout << formatted_byte_size(fibonacci(64) * sizeof(uint64_t)) << "\n";

// test polynomial
    double coeff[4] {1.2, 34.3, -1.65, 0};
    Polynomial_Homogeneous poly(4, coeff);
    std::cout << evaluate_second_order_homogeneous(poly, 0) << "\n";
    std::cout << evaluate_second_order_homogeneous(poly, -1) << "\n";
    std::cout << evaluate_second_order_homogeneous(poly, 1) << "\n";

// test fileIO
    DoubleSequence seq {"numbers"};
    seq.loadFile();
    seq.sequence.verbose();

    Polynomial_Homogeneous {seq};
}
