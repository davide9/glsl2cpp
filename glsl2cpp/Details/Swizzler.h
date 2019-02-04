#pragma once

#include "Util.h"

#include <type_traits>

namespace glsl2cpp {
namespace Details {

template<typename SubT, typename T, size_t N, size_t... Indices>
struct Swizzler
{
	static constexpr size_t Order = sizeof...(Indices);

	T myData[N];

	SubT Decay() const
	{
		return Read();
	}

	template<typename U, size_t... Other_Ns, class = std::enable_if_t<is_matrix_v<SubT> && sizeof...(Other_Ns) == Order>>
	operator Matrix_<U, Other_Ns...>() const
	{
		return Decay();
	}

	template<typename U, size_t... Other_Ns, class = std::enable_if_t<is_vector_v<SubT> && sizeof...(Other_Ns) == Order>>
	operator Vector_<U, Other_Ns...>() const
	{
		return Decay();
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator=(const U& anOther)
	{
		Write(decay(anOther));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator+=(const U& anOther)
	{
		Write(Decay() + decay(anOther));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator-=(const U& anOther)
	{
		Write(Decay() - decay(anOther));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator*=(const U& anOther)
	{
		Write(Decay() * decay(anOther));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator/=(const U& anOther)
	{
		Write(Decay() / decay(anOther));
		return *this;
	}

	template<typename U, class = std::enable_if_t<(get_total_size_v<U> == Order) && (Order > 1)>>
	bool operator==(const U& anOther) const
	{
		return Decay() == decay(anOther);
	}

	template<typename U, class = std::enable_if_t<(get_total_size_v<U> == Order) && (Order > 1)>>
	bool operator!=(const U& anOther) const
	{
		return Decay() != decay(anOther);
	}

private:
	SubT Read() const
	{
        SubT out;

        size_t i = 0;
		((out.myData[i++] = myData[Indices]), ...);

        return out;
	}

	void Write(const SubT& aIn)
	{
        size_t i = 0;
		((myData[Indices] = aIn.myData[i++]), ...);
	}
};

}
}
