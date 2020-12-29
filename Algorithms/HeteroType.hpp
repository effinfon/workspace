#ifndef HETEROTYPE_HPP_INCLUDED
#define HETEROTYPE_HPP_INCLUDED

#include <string>
#include <typeinfo>

/// TD
/*

*/

template <typename T>
struct Node {
    T value;
    std::string type {typeid(T).name()};
};



// default implementation
template <typename T>
struct TypeName
{
    static const char* Get()
    {
        return typeid(T).name();
    }
};

// a specialization for each type of those you want to support
// and don't like the string returned by typeid
template <>
struct TypeName<int>
{
    static const char* Get()
    {
        return "int";
    }
};

// usage:
//const char* name = TypeName<MyType>::Get();

/*
#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <cxxabi.h>

#define DEBUG_TYPE(x) do { typedef void(*T)x; debug_type<T>(T(), #x); } while(0)

template<typename T>
struct debug_type
{
    template<typename U>
    debug_type(void(*)(U), const std::string& p_str)
    {
        std::string str(p_str.begin() + 1, p_str.end() - 1);
        std::cout << str << " => ";
        char * name = 0;
        int status;
        name = abi::__cxa_demangle(typeid(U).name(), 0, 0, &status);
        if (name != 0) { std::cout << name << std::endl; }
        else { std::cout << typeid(U).name() << std::endl; }
        free(name);
    }
};
*/


#endif // HETEROTYPE_HPP_INCLUDED
