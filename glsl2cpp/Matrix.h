#pragma once

#include "Details/MatrixBase.h"
#include "Details/VectorOperators.h"

namespace glsl2cpp {

template<typename T, size_t N>
using Matrix = Details::Matrix_Def_t<T, N>;

using mat2i = Matrix<int, 2>;
using mat2f = Matrix<float, 2>;
using mat2d = Matrix<double, 2>;
using mat2l = Matrix<long long int, 2>;
	  
using mat3i = Matrix<int, 3>;
using mat3f = Matrix<float, 3>;
using mat3d = Matrix<double, 3>;
using mat3l = Matrix<long long int, 3>;
	  
using mat4i = Matrix<int, 4>;
using mat4f = Matrix<float, 4>;
using mat4d = Matrix<double, 4>;
using mat4l = Matrix<long long int, 4>;

}