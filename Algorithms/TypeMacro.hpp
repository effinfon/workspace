#ifndef TYPEMACRO_HPP_INCLUDED
#define TYPEMACRO_HPP_INCLUDED

#define RPD
#define RPD_ACCESS
#ifdef RPD
    #undef RPD_ACCESS
    #define RPD_ACCESS //
#endif


#define count_type uint64_t


#endif // TYPEMACRO_HPP_INCLUDED
