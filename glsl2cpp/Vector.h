#pragma once

#include "Details/VectorBase.h"
#include "Details/Util.h"

#define ALLOW_GLSL2CPP_VECTOR_NARROW_CONVERSION 1
#if ALLOW_GLSL2CPP_VECTOR_NARROW_CONVERSION
#define CAST(val) scalar_type(val)
#else
#define CAST(val) scalar_type{val}
#endif

namespace glsl2cpp {

template<typename T, size_t... Ns>
struct Vector_ : Details::VectorBase<T, sizeof...(Ns)>
{
	static constexpr size_t Order = sizeof...(Ns);

	using scalar_type = T;
	using vector_type = Vector_<T, Ns...>;
	using base_type = Details::VectorBase<T, sizeof...(Ns)>;
	using decay_type = std::conditional_t<Order == 1, scalar_type, vector_type>;

    static_assert(std::is_scalar_v<T>, "T must be a scalar type");

	using base_type::myData;

	Vector_()
	{
		((myData[Ns] = 0), ...); // should this really be initialized to 0 ?
	}

	Vector_(std::conditional_t<Order == 1, scalar_type, Details::Nothing<0>> s)
	{
		myData[0] = s;
	}

	explicit Vector_(std::conditional_t<(Order > 1), scalar_type, Details::Nothing<0>> s)
	{
		((myData[Ns] = s), ...);
	}

	template<typename... Args, class = typename std::enable_if_t<(Details::get_total_size_v<Args...> <= Order) && (Details::get_total_size_v<Args...> > 1)>>
	explicit Vector_(Args&&... args)
	{
		size_t i = 0;

		(construct_at_index(i, Details::decay(std::forward<Args>(args))), ...);
		//should the rest remain uninitialized?
	}

	const decay_type& Decay() const
	{
		return static_cast<const decay_type&>(*this);
	}

	decay_type& Decay()
	{
		return static_cast<decay_type&>(*this);
	}

	operator std::conditional_t<Order == 1, scalar_type&, Details::Nothing<0>>()
	{
		return myData[0];
	}

	operator std::conditional_t<Order == 1, scalar_type, Details::Nothing<0>>() const
	{
		return myData[0];
	}

private:
	
	template<typename U, class = std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<U>>>>
	void construct_at_index(size_t &i, U&& arg)
	{
		myData[i++] = CAST(arg);
	}

	template<typename Other, size_t... Other_Ns>
	void construct_at_index(size_t& i, const Vector_<Other, Other_Ns...>& arg)
	{
		((myData[i++] = CAST(arg.myData[Other_Ns])), ...);
	}
};

template<typename T, size_t N>
using Vector = Details::Vector_Def_t<T, N>;

using vec1i = Vector<int, 1>;
using vec1f = Vector<float, 1>;

using vec2i = Vector<int, 2>;
using vec2f = Vector<float, 2>;

using vec3i = Vector<int, 3>;
using vec3f = Vector<float, 3>;

using vec4i = Vector<int, 4>;
using vec4f = Vector<float, 4>;

}

#undef CAST
