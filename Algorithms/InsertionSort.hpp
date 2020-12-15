#ifndef INSERTIONSORT_HPP_INCLUDED
#define INSERTIONSORT_HPP_INCLUDED

#include <type_traits>
template <class T>
struct supports_less_than
{
    template <class U>
    static auto less_than_test(const U* u) -> decltype(*u < *u, char(0))
    { }

    static std::array<char, 2> less_than_test(...) { }

    static const bool value = (sizeof(less_than_test((T*)0)) == 1);
};

template<typename T>
void InsertionSort(T * contig) {
    /// "(FUNCTION) CONTRACT" ?
    // asserting that there exists the '<' operator defined for type T;
        // this is somewhat like a contract; it occurs at compile-time, etc.
    static_assert(supports_less_than<T>::value);

    // function body...

}

#endif // INSERTIONSORT_HPP_INCLUDED
