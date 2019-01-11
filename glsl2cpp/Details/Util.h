#pragma once

#include <type_traits>

namespace glsl2cpp {

template<typename T, size_t... Ns>
struct Vector_;

namespace Details {

template<size_t x = 0>
struct Nothing
{
	Nothing() = delete;
};

template<template <size_t...> class T, typename L>
struct unpack;

template<template <size_t...> class T, size_t... Ns>
struct unpack<T, std::index_sequence<Ns...>>
{
	using type = T<Ns...>;
};

template<template <size_t...> class T, typename L>
using unpack_t = typename unpack<T, L>::type;

template<typename T>
struct get_size : std::enable_if_t<std::is_scalar_v<std::decay_t<T>>, std::integral_constant<size_t, 1>> {};

template<typename T, size_t... Ns>
struct get_size<Vector_<T, Ns...>> : std::integral_constant<size_t, sizeof...(Ns)> {};

template<typename T>
constexpr size_t get_size_v = get_size<T>::value;

template<typename... Ts>
struct get_total_size;

template<>
struct get_total_size<> : std::integral_constant<size_t, 0> {};

template<typename T, typename... Ts>
struct get_total_size<T, Ts...> : std::integral_constant<size_t, get_size<T>::value + get_total_size<Ts...>::value> {};

template<typename... Ts>
constexpr size_t get_total_size_v = get_total_size<Ts...>::value;

template <class T>
constexpr auto decay(T&& t) -> decltype(t.Decay())
{
	return t.Decay();
}

template <class T>
constexpr std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<T>>, T> decay(T&& t)
{
	return t;
}

}
}