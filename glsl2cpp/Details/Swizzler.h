#pragma once

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
		VectorT vec;
		Read(vec, 0, Indices...);
		return vec;
	}

	operator VectorT() const
	{
		return Decay();
	}

	operator VectorT()
	{
		return Decay();
	}

	Swizzler& operator=(const VectorT& aVec)
	{
		Write(aVec, 0, Indices...);
		return *this;
	}

private:
	template<typename... Indices>
	void Read(VectorT& aVec, size_t i, Indices... swizz_i) const
	{
		((aVec[i++] = myData[swizz_i]), ...);
	}

	template<typename... Indices>
	void Write(const VectorT& aVec, size_t i, Indices... swizz_i)
	{
		((myData[swizz_i] = aVec[i++]), ...);
	}
};

}
}