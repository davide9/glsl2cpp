#pragma once

#include "VectorBase.h"
#include "Util.h"

namespace glsl2cpp {

template<typename T, size_t... Ns>
struct Vector_ : Details::VectorBase<T, sizeof...(Ns)>
{
	static constexpr size_t Order = sizeof...(Ns);
    static constexpr size_t Size = Order;

	using scalar_type = T;
	using vector_type = Vector_<T, Ns...>;
	using base_type = Details::VectorBase<T, sizeof...(Ns)>;
	using decay_type = std::conditional_t<Order == 1, scalar_type, vector_type>;

	static_assert(std::is_scalar_v<T>, "T must be a scalar type");
	static_assert(Order > 0, "Order must be positive");

	using base_type::myData;

	Vector_()
	{
		((myData[Ns] = 0), ...);
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
	}

	scalar_type operator[](size_t i) const { return myData[i]; }
	scalar_type& operator[](size_t i) { return myData[i]; }

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

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
	// this conversion operator enable cross-type vector assignments
	template<typename U>
	operator Vector_<U, Ns...>() const
	{
		return Vector_<U, Ns...>{*this};
	}
#endif

	vector_type& operator=(const vector_type& anOther)
	{
		((myData[Ns] = anOther.myData[Ns]), ...);
		return *this;
	}

	vector_type& operator+=(const vector_type& anOther)
	{
		((myData[Ns] += anOther.myData[Ns]), ...);
		return *this;
	}

	vector_type& operator-=(const vector_type& anOther)
	{
		((myData[Ns] -= anOther.myData[Ns]), ...);
		return *this;
	}

	vector_type& operator*=(const vector_type& anOther)
	{
		((myData[Ns] *= anOther.myData[Ns]), ...);
		return *this;
	}

	vector_type& operator*=(scalar_type aScalar)
	{
		((myData[Ns] *= aScalar), ...);
		return *this;
	}

	vector_type& operator/=(const vector_type& anOther)
	{
		((myData[Ns] /= anOther.myData[Ns]), ...);
		return *this;
	}

	template<typename U, class = std::enable_if_t<(Order > 1) && (Details::get_total_size_v<U> == Order)>>
	bool operator==(const U& anOther) const
	{
		return equal(decay(anOther));
	}

	template<typename U, class = std::enable_if_t<(Order > 1) && (Details::get_total_size_v<U> == Order)>>
	bool operator!=(const U& anOther) const
	{
		return !equal(decay(anOther));
	}

	template<typename F, typename... U>
	auto Invoke(F& aFunction, U&&... aRHS) const
	{
		return Details::vec_invoke(aFunction, *this, std::forward<U>(aRHS)...);
	}

private:

	template<typename U, class = std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<U>>>>
	void construct_at_index(size_t &i, U&& arg)
	{
		myData[i++] = GLSL2CPP_CAST(arg);
	}

	template<typename Other, size_t... Other_Ns>
	void construct_at_index(size_t& i, const Vector_<Other, Other_Ns...>& arg)
	{
		((myData[i++] = GLSL2CPP_CAST(arg.myData[Other_Ns])), ...);
	}

	bool equal(const vector_type& anOther) const
	{
		bool isEqual = true;
		((isEqual &= myData[Ns] == anOther.myData[Ns]), ...);
		return isEqual;
	}
};

}
