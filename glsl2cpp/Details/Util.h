#pragma once

#include <type_traits>

#ifndef ALLOW_GLSL2CPP_NARROW_CONVERSION
#define ALLOW_GLSL2CPP_NARROW_CONVERSION 1
#endif

#ifndef ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
#define ALLOW_GLSL2CPP_IMPLICIT_CONVERSION 1
#endif

#if ALLOW_GLSL2CPP_NARROW_CONVERSION
#define GLSL2CPP_CAST(val) scalar_type(val)
#else
#define GLSL2CPP_CAST(val) scalar_type{val}
#endif

namespace glsl2cpp {

template<typename T, size_t... Ns>
struct Vector_;

template<typename T, size_t... Ns>
struct Matrix_;

namespace Details {

template<typename SubT, typename T, size_t N, size_t... Indices>
struct Swizzler;

template<typename... T>
struct check_invocable
{
    template<typename F>
    static constexpr bool check(F&&) { return std::is_invocable_v<F, T...>; }
};

template<typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<size_t x = 0>
struct Nothing
{
	Nothing() = delete;
};

template <class T>
constexpr auto decay(T&& t)
{
    if constexpr (check_invocable<T>::check([](auto x) -> decltype(x.Decay()) { return x.Decay(); }))
    {
        return t.Decay();
    }
    else
    {
        return t;
    }
}

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

template<typename T, size_t... Ns>
struct get_size<Matrix_<T, Ns...>> : std::integral_constant<size_t, sizeof...(Ns) * sizeof...(Ns)> {};

template<typename T>
constexpr size_t get_size_v = get_size<remove_cvref_t<decltype(decay(std::declval<T>()))>>::value;

template<typename... Ts>
struct get_total_size;

template<>
struct get_total_size<> : std::integral_constant<size_t, 0> {};

template<typename T, typename... Ts>
struct get_total_size<T, Ts...> : std::integral_constant<size_t, get_size_v<T> + get_total_size<Ts...>::value> {};

template<typename... Ts>
constexpr size_t get_total_size_v = get_total_size<Ts...>::value;

template<typename T>
struct is_vector : std::false_type {};

template<typename T, size_t... Ns>
struct is_vector<Vector_<T, Ns...>> : std::true_type {};

template<typename T>
constexpr bool is_vector_v = is_vector<remove_cvref_t<decltype(decay(std::declval<T>()))>>::value;

template<typename T>
struct is_matrix: std::false_type {};

template<typename T, size_t... Ns>
struct is_matrix<Matrix_<T, Ns...>> : std::true_type {};

template<typename T>
constexpr bool is_matrix_v = is_matrix<remove_cvref_t<decltype(decay(std::declval<T>()))>>::value;

template<typename T>
constexpr bool is_scalar_v = std::is_scalar_v<decltype(decay(std::declval<T>()))>;

template<typename... Ts>
struct get_order;

template<>
struct get_order<> : std::integral_constant<size_t, 1> {};

template<typename T, typename... Ts>
struct get_order<T, Ts...> : std::integral_constant<size_t, get_size_v<T> == 1 ? get_order<Ts...>::value : (get_order<Ts...>::value == 1 ? get_size_v<T> : (get_size_v<T> == get_order<Ts...>::value ? get_order<Ts...>::value : 0))> {};

template<typename... Ts>
constexpr size_t get_order_v = get_order<Ts...>::value;

template<size_t index, typename T>
constexpr std::enable_if_t<is_vector_v<T>, decltype(std::declval<T>()[index])> get_val(T& t)
{
	return t[index];
}

template <size_t index, typename T>
constexpr std::enable_if_t<!is_vector_v<T>, T&> get_val(T& t)
{
	return t;
}

template<size_t Index, typename F, typename... ArgsT>
auto vec_invoke_one(F& aFunction, ArgsT&... someArgs)
{
	return aFunction(Details::get_val<Index>(someArgs)...);
}

template<typename F, size_t... Ns, typename... U>
auto vec_invoke_impl(F& aFunction, std::index_sequence<Ns...>, U&&... aRHS)
{
	return Vector_<decltype(vec_invoke_one<0>(aFunction, aRHS...)), Ns...>{ vec_invoke_one<Ns>(aFunction, aRHS...)... };
}

template<typename F, typename... U, typename Indices = std::make_index_sequence<get_order_v<U...>>>
auto vec_invoke(F& aFunction, U&&... aRHS)
{
	return vec_invoke_impl(aFunction, Indices{}, Details::decay(aRHS)...);
}

}
}
