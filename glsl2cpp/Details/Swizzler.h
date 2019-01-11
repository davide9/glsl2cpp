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
        VectorT vec = Read(vec);
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
		Write(aVec);
		return *this;
	}

private:
	VectorT Read() const
	{
        VectorT vec;

        size_t i;
		((aVec[i++] = myData[Indices]), ...);

        return vec;
	}

	void Write(const VectorT& aVec)
	{
        size_t i;
		((myData[Indices] = aVec[i++]), ...);
	}
};

}
}
