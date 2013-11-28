#ifndef SGLMATH_H
#define SGLMATH_H
#include "../sgl.h"
#include <type_traits>

#if defined(_MSC_VER ) && (_MSC_VER  < 1700 )
    #define constexpr //no vs support for constexpr (thanks MS)
#endif

namespace sgl { namespace math{

    template <typename T> inline constexpr
    int signum(T x, std::false_type) {
        return T(0) < x;
    }

    template <typename T> inline constexpr
    int signum(T x, std::true_type) {
        return (T(0) < x) - (x < T(0));
    }

    template <typename T> inline constexpr
    int signum(T x) {
        return signum(x, std::is_signed<T>());
    }
    template <typename T> inline constexpr
    int sign(T x) {
        return signum(x, std::is_signed<T>());
    }

}} //end sgl::math

#endif // SGLMATH_H
