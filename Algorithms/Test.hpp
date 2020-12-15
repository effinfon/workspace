#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED


/// TD
/*
    all tests need to be done on multiple algorithm implementations, and the algorithms need to confirm each other, thus having a "non-explicitly specified method of verification" (albeit, this is just a probabilistic method, more than not, compared to the programmer explicitly computing the scenarios; or is it ?!)

*/


#include "StringProcessing.hpp"
void TestStringProcessing() {
    std::vector<std::string> test {"I identify", "identify", "123idne", "_identi_fy", "uiasbfui8723bf23jfb2io"};
    std::vector<bool> results;
    for(std::string a : test) {
        bool temp = isIdentifier(a);
        results.push_back(temp);
        std::cout << ((temp) ? "true" : "false") << " ";
    }

    std::vector<std::string> unique = find_unique(std::string("This is just a very short string, but later on I will input a whole text file with some pages from wikipedia"));
    for(auto a : unique) std::cout << a << " ";
}

#include "Sort.hpp"
    /// Dependencies
    #include "RawArray.hpp"

    /// Internal functions to a function (?); although, might as well use a class object, but still... flexibility (?!)
//template<typename T>
//int cmp(T& a, T& b) {
int cmp(int& a, int& b) {
    if (a < b) return -1;
    else if (a > b) return +1;
    else return 0;
}

void TestSort() {
        // bi-dimensional array -> get the size of the bi-array, or of any of its internal arrays -> automate the loops underneath
    int array1[] {1, 4, 6, 2, 7, 5, 1, -1, -2, 56, -129, 5, 5};
//    int array2[] = array;   // if only there were array-semantics...
    int array2[] {1, 4, 6, 2, 7, 5, 1, -1, -2, 56, -129, 5, 5};
    int array3[] {1, 4, 6, 2, 7, 5, 1, -1, -2, 56, -129, 5, 5};

    int array4[] {1, 4, 6, 2, 7, 5, 1, -1, -2, 56, -129, 5, 5};
    int array5[] {1, 4, 6, 2, 7, 5, 1, -1, -2, 56, -129, 5, 5};
    int array6[] {1, 4, 6, 2, 7, 5, 1, -1, -2, 56, -129, 5, 5};

    selection_sort<int>(array1, sizeof(array1) / sizeof(int), cmp, true);
    insertion_sort<int>(array2, sizeof(array2) / sizeof(int), cmp, true);
    bubble_sort<int>(array3, sizeof(array3) / sizeof(int), cmp, true);

    for(count_type i = 0; i < sizeof(array1) / sizeof(int); i++) {
        std::cout << array1[i] << " ";
    }   std::cout << "\n";
    for(count_type i = 0; i < sizeof(array2) / sizeof(int); i++) {
        std::cout << array2[i] << " ";
    }   std::cout << "\n";
    for(count_type i = 0; i < sizeof(array3) / sizeof(int); i++) {
        std::cout << array3[i] << " ";
    }   std::cout << "\n";
    for(count_type i = 0; i < sizeof(array4) / sizeof(int); i++) {
        std::cout << array4[i] << " ";
    }   std::cout << "\n";
    for(count_type i = 0; i < sizeof(array5) / sizeof(int); i++) {
        std::cout << array5[i] << " ";
    }   std::cout << "\n";
    for(count_type i = 0; i < sizeof(array6) / sizeof(int); i++) {
        std::cout << array6[i] << " ";
    }

    int** arrays = new int* [3 * sizeof(int**)];
    arrays[0] = array1;
    arrays[1] = array2;
    arrays[2] = array3;
    uint32_t* sizes = new uint32_t[3];
    for(int i = 0; i < 3; i++) sizes[i] = sizeof(array1) / sizeof(int); /* sizeof(arrays[i]) / sizeof(int) [this won't work, because the pointer type is recognized here and not the array type*/;

    std::cout << "\nTest for identicity: " << ((equal_arrays(arrays, 3, sizes) ? "true" : "false")) << "\n";
}

#include "PrimalityTest.hpp"

bool TestPrimalityTest() {
    int* sieve1 = sieve_Eratosthenes_v1(1000);
    for(int i = 0; i <= 1000; i++) {
        std::cout << "[" << i << "]: " << sieve1[i] << ", ";
    }

    std::cout << "\n";
    int* sieve2 = sieve_Eratosthenes_v0(1000);
    for(int i = 0; i <= 1000; i++) {
        std::cout << "[" << i << "]: " << sieve2[i] << ", ";
    }

    return true;
}

#include "LinkedList.hpp"

void TestLinkedList() {
    RawSinglyLinkedNode* node1 = new RawSinglyLinkedNode();
    delete node1;
    RawSinglyLinkedNode* node2 = new RawSinglyLinkedNode[100];
    delete [] node2;

    RawSinglyLinkedList* list1 = new RawSinglyLinkedList();
    delete list1;
    RawSinglyLinkedList* list2 = new RawSinglyLinkedList[100];
    delete [] list2;
}

#include "Search.hpp"


void TestSearch() {
    template<typename T, count_type cardinal_arg>
    struct Test {
        count_type cardinal {cardinal_arg};
        T array[cardinal_arg] {};

        Test() {}
    };

}

#endif // TEST_HPP_INCLUDED
