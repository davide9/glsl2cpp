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

template<typename T, size_t N>
struct Vector_Def
{
    template<typename T, typename IS>
    struct Vector_Def_Impl;

    template<typename T, size_t... Ns>
    struct Vector_Def_Impl<T, std::index_sequence<Ns...>>
    {
        using type = Vector_<T, Ns...>;
    };

    using type = typename Vector_Def_Impl<T, std::make_index_sequence<N>>::type;
};

template<typename T, size_t N>
using Vector_Def_t = typename Vector_Def<T, N>::type;

template<typename SubT, typename T, size_t N, size_t... Indices>
struct Swizzler;

template<typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<size_t x = 0>
struct Nothing
{
	Nothing() = delete;
};

template<typename T>
struct decay_type
{
    template<typename U>
    static typename U::decay_type decay_(std::add_pointer_t<typename U::decay_type>);
    template<typename U>
    static U decay_(...);

    template<typename U>
    static std::true_type will_decay_(std::add_pointer_t<typename U::decay_type>);
    template<typename U>
    static std::false_type will_decay_(...);

    using type = decltype(decay_<remove_cvref_t<T>>(nullptr));
    static constexpr bool will_decay = decltype(will_decay_<remove_cvref_t<T>>(nullptr))::value;
};

template<typename T>
using decay_type_t = typename decay_type<T>::type;

template<typename T>
constexpr bool will_decay_v = decay_type<T>::will_decay;

template<typename T>
constexpr auto decay(T&& t) -> std::enable_if_t<will_decay_v<T>, decltype(std::forward<T>(t).Decay())> { return std::forward<T>(t).Decay(); }

template<typename T>
constexpr auto decay(T&& t) -> std::enable_if_t<!will_decay_v<T>, decltype(std::forward<T>(t))> { return std::forward<T>(t); }

template<typename T>
struct get_size_impl : std::integral_constant<size_t, 1> {};

template<typename T, size_t... Ns>
struct get_size_impl<Vector_<T, Ns...>> : std::integral_constant<size_t, sizeof...(Ns)> {};

template<typename T, size_t... Ns>
struct get_size_impl<Matrix_<T, Ns...>> : std::integral_constant<size_t, sizeof...(Ns) * sizeof...(Ns)> {};

template<typename T>
struct get_size : get_size_impl<decay_type_t<T>> {};

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

template<typename T>
struct is_vector_impl : std::false_type {};

template<typename T, size_t... Ns>
struct is_vector_impl<Vector_<T, Ns...>> : std::true_type {};

template<typename T>
struct is_vector : is_vector_impl<decay_type_t<T>> {};

template<typename T>
constexpr bool is_vector_v = is_vector<T>::value;

template<typename T>
struct is_matrix: std::false_type {};

template<typename T, size_t... Ns>
struct is_matrix<Matrix_<T, Ns...>> : std::true_type {};

template<typename T>
constexpr bool is_matrix_v = is_matrix<decay_type_t<T>>::value;

template<typename T>
constexpr bool is_scalar_v = std::is_scalar_v<decay_type_t<T>>;

template<typename... Ts>
struct get_order;

template<>
struct get_order<> : std::integral_constant<size_t, 1> {};

template<typename T, typename... Ts>
struct get_order<T, Ts...> : std::integral_constant<size_t, get_size_v<T> == 1 ? get_order<Ts...>::value : (get_order<Ts...>::value == 1 ? get_size_v<T> : (get_size_v<T> == get_order<Ts...>::value ? get_order<Ts...>::value : 0))> {};

template<typename... Ts>
constexpr size_t get_order_v = get_order<Ts...>::value;

template<typename T>
struct vec_forwarding_proxy
{
    constexpr vec_forwarding_proxy(T& aValue) : value{ aValue } {}

    template<size_t index>
    constexpr auto&& get() {
        if constexpr (is_vector_v<T>)
        {
            if constexpr (std::is_rvalue_reference_v<T>)
            {
                return  std::move(value[index]);
            }
            else
            {
                return value[index];
            }
        }
        else
        {
            return value;
        }
    }

    std::remove_reference_t<T>& value;
};

template<size_t Index, typename F, typename... ArgsT>
auto vec_invoke_line(F& aFunction, ArgsT&&... someArgs)
{
	return aFunction(someArgs.get<Index>()...);
}

template<typename F, size_t... Ns, typename... ArgsT>
auto vec_invoke_impl(F&& aFunction, std::index_sequence<Ns...>, ArgsT&&... aRHS)
{
    using result_type = decltype(vec_invoke_line<0>(aFunction, vec_forwarding_proxy<decltype(std::forward<ArgsT>(aRHS))>{aRHS}...));
    return Vector_Def_t<result_type, sizeof...(Ns)>{ vec_invoke_line<Ns>(aFunction, vec_forwarding_proxy<decltype(std::forward<ArgsT>(aRHS))>{aRHS}...)... };
}

template<typename F, typename... U>
auto vec_invoke(F&& aFunction, U&&... aRHS)
{
	return vec_invoke_impl(std::forward<F>(aFunction), std::make_index_sequence<get_order_v<U...>>{}, decay(std::forward<U>(aRHS))...);
}

}
}
