#pragma once

#include "VectorImpl.h"

#include <cmath>

#define DEFINE_FUNCTION(functionName, functionImpl) \
template<typename T, typename... Us> \
inline auto functionName(const T& aVector, Us&&... someArgs) \
{ \
    return ::glsl2cpp::Details::decay(aVector).Invoke([](auto&&... args) { return functionImpl(std::forward<decltype(args)>(args)...); }, std::forward<Us>(someArgs)...); \
}

#define DEFINE_STD_FUNCTION(functionName) DEFINE_FUNCTION(functionName, std::functionName)
#define DEFINE_GLSL2CPP_FUNCTION(functionName) DEFINE_FUNCTION(functionName, ::glsl2cpp::Functions::functionName)

namespace glsl2cpp {

namespace Functions{

template<typename T0, typename T1, typename T2>
auto Clamp(const T0& v, const T1& min, const T2& max) -> T0
{
    return v < min ? min : v > max ? max : v;
}

}

DEFINE_STD_FUNCTION(abs)
DEFINE_STD_FUNCTION(acos)
DEFINE_STD_FUNCTION(asin)
DEFINE_STD_FUNCTION(atan)
DEFINE_STD_FUNCTION(atan2)

DEFINE_STD_FUNCTION(cos)
DEFINE_STD_FUNCTION(cosh)
DEFINE_STD_FUNCTION(exp)
DEFINE_STD_FUNCTION(fabs)
DEFINE_STD_FUNCTION(fmod)
DEFINE_STD_FUNCTION(log)
DEFINE_STD_FUNCTION(log2)
DEFINE_STD_FUNCTION(log10)
DEFINE_STD_FUNCTION(pow)
DEFINE_STD_FUNCTION(sin)
DEFINE_STD_FUNCTION(sinh)
DEFINE_STD_FUNCTION(tan)
DEFINE_STD_FUNCTION(tanh)

DEFINE_GLSL2CPP_FUNCTION(Clamp)

}

#undef DEFINE_FUNCTION
#undef DEFINE_STD_FUNCTION
#undef DEFINE_GLSL2CPP_FUNCTION
