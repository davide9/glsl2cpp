#pragma once

#include "VectorImpl.h"

namespace glsl2cpp {
namespace Details {

template<typename T, size_t N>
struct Matrix_Def
{
    template<typename T>
    struct M
    {};

    template<size_t... Ns>
    struct M<std::index_sequence<Ns...>>
    {
        using type = Matrix_<T, Ns...>;
    };

	using type = typename M<std::make_index_sequence<N>>::type;
};

template<typename T, size_t N>
using Matrix_Def_t = typename Matrix_Def<T, N>::type;

template<typename T, size_t N>
struct MatrixSwizzlerFactory
{
	template<size_t M, size_t... Indices>
	struct SwizzlerType
	{
		using type = ::glsl2cpp::Details::Swizzler<Matrix_Def_t<T, M>, T, N * N, Indices...>;
	};
};

template<typename T, size_t N, template<size_t...> class SwizzlerT = MatrixSwizzlerFactory<T, N>::SwizzlerType>
struct BaseMatrix_
{
	BaseMatrix_() : myData{} {}

	union
	{
		T myData[N * N];
		T myMat[N][N];
		Details::Vector_Def_t<T, N> myVec[N];
	};
};

template<typename T, template<size_t...> class SwizzlerT>
struct BaseMatrix_<T, 3, SwizzlerT>
{
	BaseMatrix_() : myData{} {}

	union
	{
		T myData[3 * 3];
		T myMat[3][3];
		Details::Vector_Def_t<T, 3> myVec[3];

		struct
		{
			Details::Vector_Def_t<T, 3> myXAxis;
			Details::Vector_Def_t<T, 3> myYAxis;
			Details::Vector_Def_t<T, 3> myZAxis;
		};
	};
};

template<typename T, template<size_t...> class SwizzlerT>
struct BaseMatrix_<T, 4, SwizzlerT>
{
	BaseMatrix_() : myData{} {}

	template<size_t M, size_t... Indices>
	using Swizzler = typename SwizzlerT<M, Indices...>::type;

	union
	{
		T myData[4 * 4];
		T myMat[4][4];
		Details::Vector_Def_t<T, 4> myVec[4];

		struct
		{
			Details::Vector_Def_t<T, 4> myXAxis;
			Details::Vector_Def_t<T, 4> myYAxis;
			Details::Vector_Def_t<T, 4> myZAxis;
			Details::Vector_Def_t<T, 4> myPosition;
		};

		Swizzler<3, 0, 1, 2, 4, 5, 6, 8, 9, 10> myMat3x3;
	};
};

}

template<typename T, size_t... Ns>
struct Matrix_ : Details::BaseMatrix_<T, sizeof...(Ns)>
{
	static constexpr size_t Order = sizeof...(Ns);
	static constexpr size_t Size = Order * Order;

	using scalar_type = T;
	using vector_type = Vector_<T, Ns...>;
	using matrix_type = Matrix_<T, Ns...>;
	using base_type = Details::BaseMatrix_<T, sizeof...(Ns)>;

	static_assert(std::is_scalar_v<T>, "T must be a scalar type");
	static_assert(Order > 1, "Order must be positive and greater than 1");

	using base_type::myMat;

	const matrix_type& Decay() const
	{
		return *this;
	}

	matrix_type& Decay()
	{
		return *this;
	}

	Matrix_() = default;

	explicit Matrix_(scalar_type aScalar)
	{
		construct_from(aScalar);
	}

	template<typename U>
	explicit Matrix_(U&& aVal)
		: Matrix_(scalar_type(1))
	{
		construct_from(Details::decay(std::forward<U>(aVal)));
	}

	template<typename... Args, class = typename std::enable_if_t<sizeof...(Args) == Order || sizeof...(Args) == Size>>
	explicit Matrix_(Args&&... args)
	{
		construct_from(Details::decay(std::forward<Args>(args))...);
	}

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
	template<typename U>
	operator Matrix_<U, Ns...>() const
	{
		return Matrix_<U, Ns...>{*this};
	}
#endif

	vector_type operator[](size_t i) const { return myVec[i]; }
	vector_type& operator[](size_t i) { return myVec[i]; }

	matrix_type& operator=(const matrix_type& anOther)
	{
		((myVec[Ns] = anOther.myVec[Ns]), ...);
		return *this;
	}

	matrix_type& operator+=(const matrix_type& anOther)
	{
		((myVec[Ns] += anOther.myVec[Ns]), ...);
		return *this;
	}

	matrix_type& operator-=(const matrix_type& anOther)
	{
		((myVec[Ns] -= anOther.myVec[Ns]), ...);
		return *this;
	}

	matrix_type& operator*=(scalar_type aScalar)
	{
		((myVec[Ns] *= aScalar), ...);
		return *this;
	}

	matrix_type& operator*=(const matrix_type& anOther)
	{
		auto tmp = transpose();
		((myVec[Ns] = anOther.myVec[Ns] * tmp), ...);
		return *this;
	}

	template<typename U, class = std::enable_if_t<(Order > 1) && (Details::get_total_size_v<U> == Size)>>
	bool operator==(const U& anOther) const
	{
		return equal(decay(anOther));
	}

	template<typename U, class = std::enable_if_t<(Order > 1) && (Details::get_total_size_v<U> == Size)>>
	bool operator!=(const U& anOther) const
	{
		return !equal(decay(anOther));
	}

	vector_type row(size_t i) const
	{
		vector_type row{ (myMat[Ns][i])... };
		return row;
	}

	const vector_type& col(size_t i) const
	{
		return myVec[i];
	}

	matrix_type transpose() const
	{
		Matrix_<T, Ns...> result{ row(Ns)... };
		return result;
	}

private:

    template<typename U, class = std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<U>>>>
	void construct_from(U&& aScalar)
	{
		((myMat[Ns][Ns] = GLSL2CPP_CAST(aScalar)), ...);
	}

    template<typename U, class = std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<U>>>>
	void construct_at(size_t anIndex, U&& aScalar)
	{
		myData[anIndex] = GLSL2CPP_CAST(aScalar);
	}

	template<typename U, size_t... Other_Ns>
	std::enable_if_t<(sizeof...(Other_Ns) <= Order)> construct_from(const Matrix_<U, Other_Ns...>& anOther)
	{
		((construct_line(Other_Ns, anOther.myVec[Other_Ns])), ...);
	}

	template<typename... ArgsT>
	std::enable_if_t<sizeof...(ArgsT) == Order> construct_from(ArgsT&&... someOthers)
	{
		((construct_line(Ns, someOthers)), ...);
	}

	template<typename... ArgsT>
	std::enable_if_t<sizeof...(ArgsT) == Size> construct_from(ArgsT&&... someOthers)
	{
		size_t i = 0;

		(construct_at(i++, Details::decay(std::forward<ArgsT>(someOthers))), ...);
	}

	template<typename U, size_t... Other_Ns>
	void construct_line(size_t anIndex, const Vector_<U, Other_Ns...>& aLine)
	{
		((myVec[anIndex][Other_Ns] = GLSL2CPP_CAST(aLine[Other_Ns])), ...);
	}

	bool equal(const matrix_type& anOther) const
	{
		bool isEqual = true;
		((isEqual &= myVec[Ns] == anOther.myVec[Ns]), ...);
		return isEqual;
	}
};

}
