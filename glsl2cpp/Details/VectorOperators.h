#pragma once

#include "VectorImpl.h"

namespace glsl2cpp {
namespace Operators {

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() + std::declval<V>())>
inline Vector_<Ret, Ns...> sum(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
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

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() * std::declval<V>())>
inline Vector_<Ret, Ns...> mul(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result *= aRHS;
	return result;
}

template<typename U, typename V, size_t... Ns, typename Ret = decltype(std::declval<U>() / std::declval<V>())>
inline Vector_<Ret, Ns...> div(const Vector_<U, Ns...>& aLHS, const Vector_<V, Ns...>& aRHS)
{
	Vector_<Ret, Ns...> result{ aLHS };
	result /= aRHS;
	return result;
}

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

}