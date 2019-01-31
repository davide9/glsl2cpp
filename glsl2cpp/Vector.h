#pragma once

#define ALLOW_GLSL2CPP_VECTOR_NARROW_CONVERSION 1

#include "Details/VectorImpl.h"
#include "Details/VectorOperators.h"
#include "Details/VectorFunctions.h"

namespace glsl2cpp {

template<typename T, size_t N>
using Vector = Details::Vector_Def_t<T, N>;

using vec1i = Vector<int, 1>;
using vec1f = Vector<float, 1>;
using vec1l = Vector<long long int, 1>;

using vec2i = Vector<int, 2>;
using vec2f = Vector<float, 2>;
using vec2l = Vector<long long int, 2>;

using vec3i = Vector<int, 3>;
using vec3f = Vector<float, 3>;
using vec3l = Vector<long long int, 3>;

using vec4i = Vector<int, 4>;
using vec4f = Vector<float, 4>;
using vec4l = Vector<long long int, 4>;

}
