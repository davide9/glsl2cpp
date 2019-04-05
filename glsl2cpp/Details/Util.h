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

template<typename T>
struct is_vector_ : std::false_type
{};

template<typename T, size_t... Ns>
struct is_vector_<Vector_<T, Ns...>> : std::true_type
{};

template<typename T, size_t N, size_t... Indices, size_t... Ns>
struct is_vector_<Swizzler<Vector_<T, Ns...>, T, N, Indices...>> : std::true_type
{};

template<typename T>
struct is_vector : is_vector_<remove_cvref_t<T>>
{};

template<typename T>
constexpr bool is_vector_v = is_vector<T>::value;

template<typename T>
struct is_matrix_ : std::false_type
{};

template<typename T, size_t... Ns>
struct is_matrix_<Matrix_<T, Ns...>> : std::true_type
{};

template<typename T, size_t N, size_t... Indices, size_t... Ns>
struct is_matrix_<Swizzler<Matrix_<T, Ns...>, T, N, Indices...>> : std::true_type
{};

template<typename T>
struct is_matrix : is_matrix_<remove_cvref_t<T>>
{};

template<typename T>
constexpr bool is_matrix_v = is_matrix<T>::value;
 
template <class T>
constexpr auto decay(T&& t)
{
    if constexpr (is_vector_v<T> || is_matrix_v<T>)
    {
        return t.Decay();
    }
    else
    {
        return t;
    }
}

template<typename T>
struct decay_type
{
    using type = decltype(decay(std::declval<T>()));
};

template<typename T>
using decay_type_t = typename decay_type<T>::type;

template<typename T, bool hasSize>
struct get_size_;

template<typename T>
struct get_size_<T, true> : std::integral_constant<size_t, T::Size> {};

template<typename T>
struct get_size_<T, false> : std::integral_constant<size_t, 1> {};

template<typename T>
struct get_size : get_size_<decay_type_t<T>, is_vector_v<decay_type_t<T>> || is_matrix_v<T>> {};

template<typename T>
constexpr size_t get_size_v = get_size<T>::value;

template<typename... Ts>
struct get_total_size;

template<>
struct get_total_size<> : std::integral_constant<size_t, 0> {};

template<typename T, typename... Ts>
struct get_total_size<T, Ts...> : std::integral_constant<size_t, get_size_v<T> + get_total_size<Ts...>::value> {};

template<typename... Ts>
constexpr size_t get_total_size_v = get_total_size<Ts...>::value;

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
