#pragma once

#include "Util.h"

#include <type_traits>

namespace glsl2cpp {
namespace Details {

template<typename VectorT, typename T, size_t N, size_t... Indices>
struct Swizzler
{
	static constexpr size_t Order = sizeof...(Indices);

	T myData[N];

	VectorT Decay() const
	{
		return Read();
	}

	template<typename U, size_t... Other_Ns, class = std::enable_if_t<sizeof...(Other_Ns) == Order>>
	operator Vector_<U, Other_Ns...>() const
	{
		return Decay();
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator=(const U& aVec)
	{
		Write(decay(aVec));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator+=(const U& aVec)
	{
		Write(Decay() + decay(aVec));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator-=(const U& aVec)
	{
		Write(Decay() - decay(aVec));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator*=(const U& aVec)
	{
		Write(Decay() * decay(aVec));
		return *this;
	}

	template<typename U, class = std::enable_if_t<get_total_size_v<U> == Order>>
	Swizzler& operator/=(const U& aVec)
	{
		Write(Decay() / decay(aVec));
		return *this;
	}

	template<typename U, class = std::enable_if_t<(get_total_size_v<U> == Order) && (Order > 1)>>
	bool operator==(const U& aVec) const
	{
		return Decay() == decay(aVec);
	}

	template<typename U, class = std::enable_if_t<(get_total_size_v<U> == Order) && (Order > 1)>>
	bool operator!=(const U& aVec) const
	{
		return Decay() != decay(aVec);
	}

private:
	VectorT Read() const
	{
        VectorT vec;

        size_t i = 0;
		((vec[i++] = myData[Indices]), ...);

        return vec;
	}

	void Write(const VectorT& aVec)
	{
        size_t i = 0;
		((myData[Indices] = aVec[i++]), ...);
	}
};

}
}
