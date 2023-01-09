#pragma once

#include <package_defs.hpp>
///
///  Namespace stuff
///

#define SECTIONS_NS_HEAD  \
  NS_HEAD namespace sections {

#define SECTIONS_NS_FOOT  \
  NS_FOOT }


SECTIONS_NS_HEAD

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
typedef signed int     s32;
typedef float          f32;
typedef double         f64;

template <typename T>
T revPrimative(const T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}

SECTIONS_NS_FOOT
