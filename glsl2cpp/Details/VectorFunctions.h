#pragma once

#include "VectorImpl.h"

#include <cmath>
#include <type_traits>
#include <utility>

#define DEFINE_FUNCTION(functionName, functionImpl) \
namespace Details { struct try_apply_##functionName { \
template <class Tuple, std::size_t... I>\
constexpr auto operator()(Tuple&& t, std::index_sequence<I...>) -> decltype(functionImpl(std::get<I>(std::forward<Tuple>(t))...));\
};}\
template<typename... ArgsT> \
inline auto functionName(ArgsT&&... someArgs) -> std::enable_if_t< \
 glsl2cpp_detail_check_invoke_<glsl2cpp::Details::try_apply<Details::try_apply_##functionName>, ArgsT...>::value \
, typename glsl2cpp_detail_check_invoke_<glsl2cpp::Details::try_apply<Details::try_apply_##functionName>, ArgsT...>::result_type \
>\
{ \
    return ::glsl2cpp::Details::vec_invoke([](auto&&... args){ return functionImpl(std::forward<decltype(args)>(args)...); }, std::forward<ArgsT>(someArgs)...);\
}

#define DEFINE_STD_FUNCTION(functionName) DEFINE_FUNCTION(functionName, std::functionName)
#define DEFINE_GLSL2CPP_FUNCTION(functionName) DEFINE_FUNCTION(functionName, ::glsl2cpp::Functions::functionName)

namespace glsl2cpp {
namespace Details {

template<typename T>
struct try_apply
{
    template <class Tuple>
    constexpr auto operator()(Tuple&& t) -> decltype(std::declval<T>()(std::forward<Tuple>(t),
                                                                       std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{}));
};

}
}

template<typename T, typename... ArgsT>
struct glsl2cpp_detail_check_invoke_
{
    template<typename F, typename... Ts>
    static constexpr bool check(F&&, Ts&&...) {
        return std::is_invocable_v<F, Ts...>;
    }

    static constexpr bool value = check([](auto c, auto x) -> decltype(c(x)) {}, T{}, std::tuple<::glsl2cpp::Details::get_linear_type_t<ArgsT>...>{});

    template<bool isInvocable, typename... ArgsT>
    struct result_type_;
    
    template<typename... Args>
    struct result_type_<true, Args...>
    {
        using linear_type = decltype(std::declval<T>()(std::tuple<::glsl2cpp::Details::get_linear_type_t<Args>...>{}));

        using type = glsl2cpp::Details::Vector_Def_t<linear_type, ::glsl2cpp::Details::get_order_v<Args...>>;
    };
    
    template<typename... Args>
    struct result_type_<false, Args...>
    {
        using type = void;
    };
    
    using result_type = typename result_type_<value, ArgsT...>::type;
};

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
