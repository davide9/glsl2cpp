#pragma once

#include "VectorImpl.h"

#include <cmath>

namespace glsl2cpp {
namespace Operators {

template<typename T>
using Vector3_ = Vector_<T, 0, 1, 2>;

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() + std::declval<V>())>
inline Vector_<Ret, Ns...> sum(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result += aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() + std::declval<V>())>
inline Matrix_<Ret, Ns...> sum(const Matrix_<U, Ns...>& aLHS, const Matrix_<V, Ns...>& aRHS)
{
	Matrix_<Ret, Ns...> result{ aLHS };
	result += aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() - std::declval<V>())>
inline Vector_<Ret, Ns...> diff(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result -= aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() - std::declval<V>())>
inline Matrix_<Ret, Ns...> diff(const Matrix_<U, Ns...>& aLHS, const Matrix_<V, Ns...>& aRHS)
{
	Matrix_<Ret, Ns...> result{ aLHS };
	result -= aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Vector_<Ret, Ns...> mul(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result *= aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Vector_<Ret, Ns...> mul(U aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aRHS };
	result *= aLHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Vector_<Ret, Ns...> mul(const Vector_<U, Ns...>& aLHS, V aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result *= aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Matrix_<Ret, Ns...> mul(const Matrix_<U, Ns...>& aLHS, const Matrix_<V, Ns...>& aRHS)
{
	Matrix_<Ret, Ns...> result{ aLHS };
	result *= aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Matrix_<Ret, Ns...> mul(U aLHS, const Matrix_<V, Ns...>& aRHS)
{
	Matrix_<Ret, Ns...> result{ aRHS };
	result *= aLHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Matrix_<Ret, Ns...> mul(const Matrix_<U, Ns...>& aLHS, V aRHS)
{
	Matrix_<Ret, Ns...> result{ aLHS };
	result *= aRHS;
	return result;
}

template<typename T, size_t... Ns>
inline T linear_sum(const Vector_<T, Ns...>& aVector)
{
	return (aVector[Ns] + ...);
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Vector_<Ret, Ns...> mul(const Vector_<U, Ns...>& aLHS, const Matrix_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ linear_sum(aLHS * aRHS[Ns])... };
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Vector_<Ret, Ns...> mul(const Matrix_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	return mul(aRHS, aLHS.transpose());
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() / std::declval<V>())>
inline Vector_<Ret, Ns...> div(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result /= aRHS;
	return result;
}

template<typename U, typename V, typename Ret = decltype(std::declval<V>() * std::declval<U>())>
inline Vector3_<Ret> vector_cross(const Vector3_<U>& aLHS, const Vector3_<V>& aRHS)
{
	return Vector3_<Ret>{ aLHS[1] * aRHS[2] - aLHS[2] * aRHS[1], aLHS[2] * aRHS[0] - aLHS[0] * aRHS[2], aLHS[0] * aRHS[1] - aLHS[1] * aRHS[0] };
}

template<typename T>
inline float sqrt(T&& aVal) { return std::sqrtf(std::forward<T>(aVal)); }
inline double sqrt(double aVal) { return std::sqrt(aVal); }

}

template<typename U, typename V>
inline auto operator+(const U& aLHS, const V& aRHS) -> decltype(Operators::sum(decay(aLHS), decay(aRHS)))
{
	return Operators::sum(decay(aLHS), decay(aRHS));
}

template<typename U, typename V>
inline auto operator-(const U& aLHS, const V& aRHS) -> decltype(Operators::diff(decay(aLHS), decay(aRHS)))
{
	return Operators::diff(decay(aLHS), decay(aRHS));
}

template<typename U, typename V>
inline auto operator*(const U& aLHS, const V& aRHS) -> decltype(Operators::mul(decay(aLHS), decay(aRHS)))
{
	return Operators::mul(decay(aLHS), decay(aRHS));
}

template<typename U, typename V>
inline auto operator/(const U& aLHS, const V& aRHS) -> decltype(Operators::div(decay(aLHS), decay(aRHS)))
{
	return Operators::div(decay(aLHS), decay(aRHS));
}

template<typename U, typename V>
inline auto dot(const U& aLHS, const V& aRHS) -> decltype(Operators::linear_sum(aLHS * aRHS))
{
	return Operators::linear_sum(aLHS * aRHS);
}

template<typename U, typename V>
inline auto cross(const U& aLHS, const V& aRHS) -> decltype(Operators::vector_cross(decay(aLHS), decay(aRHS)))
{
	return Operators::vector_cross(decay(aLHS), decay(aRHS));
}

template<typename T>
inline auto length2(const T& aVector)
{
	return dot(aVector, aVector);
}

template<typename T>
inline auto length(const T& aVector)
{
	return Operators::sqrt(length2(aVector));
}

}