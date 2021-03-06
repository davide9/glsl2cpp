#include "pch.h"

#define ALLOW_GLSL2CPP_IMPLICIT_CONVERSION 1
#define ALLOW_GLSL2CPP_NARROW_CONVERSION 1

#include <Vector.h>
#include <Matrix.h>

#include <memory>
#include <tuple>

TEST(Vector1, Construction)
{
	glsl2cpp::Vector<int, 1> vDefault;
	EXPECT_EQ(vDefault, 0);

	glsl2cpp::vec1i vScalar(1);
	EXPECT_EQ(vScalar, 1);

	glsl2cpp::vec1i vCopy(vScalar);
	EXPECT_EQ(vCopy, 1);

	glsl2cpp::vec1i vSwizzlerCopy(vScalar.x);
	EXPECT_EQ(vSwizzlerCopy, 1);
}

TEST(Vector2, Construction)
{
	glsl2cpp::vec2i vDefault;
	EXPECT_EQ(vDefault.x, 0);
	EXPECT_EQ(vDefault.y, 0);

	glsl2cpp::vec2i vScalar(1);
	EXPECT_EQ(vScalar.x, 1);
	EXPECT_EQ(vScalar.y, 1);

	glsl2cpp::vec2i vScalars(2, 3);
	EXPECT_EQ(vScalars.x, 2);
	EXPECT_EQ(vScalars.y, 3);

	glsl2cpp::vec2i vCopy(vScalars);
	EXPECT_EQ(vCopy.x, 2);
	EXPECT_EQ(vCopy.y, 3);

	glsl2cpp::vec2i vMix(glsl2cpp::vec1i{ 4 }, 5);
	EXPECT_EQ(vMix.x, 4);
	EXPECT_EQ(vMix.y, 5);

	glsl2cpp::vec2i vSwizzlerCopy(vMix.xy);
	EXPECT_EQ(vSwizzlerCopy.x, 4);
	EXPECT_EQ(vSwizzlerCopy.y, 5);
}

TEST(Vector3, Construction)
{
	glsl2cpp::vec3i vDefault;
	EXPECT_EQ(vDefault.x, 0);
	EXPECT_EQ(vDefault.y, 0);
	EXPECT_EQ(vDefault.z, 0);

	glsl2cpp::vec3i vScalar(1);
	EXPECT_EQ(vScalar.x, 1);
	EXPECT_EQ(vScalar.y, 1);
	EXPECT_EQ(vScalar.z, 1);

	glsl2cpp::vec3i vScalars(2, 3, 4);
	EXPECT_EQ(vScalars.x, 2);
	EXPECT_EQ(vScalars.y, 3);
	EXPECT_EQ(vScalars.z, 4);

	glsl2cpp::vec3i vCopy(vScalars);
	EXPECT_EQ(vCopy.x, 2);
	EXPECT_EQ(vCopy.y, 3);
	EXPECT_EQ(vCopy.z, 4);

	glsl2cpp::vec3i vMix(glsl2cpp::vec2i{ 4 }, 5);
	EXPECT_EQ(vMix.x, 4);
	EXPECT_EQ(vMix.y, 4);
	EXPECT_EQ(vMix.z, 5);

	glsl2cpp::vec3i vSwizzlerMix(vMix.xy, 5);
	EXPECT_EQ(vSwizzlerMix.x, 4);
	EXPECT_EQ(vSwizzlerMix.y, 4);
	EXPECT_EQ(vSwizzlerMix.z, 5);
}

TEST(Vector4, Construction)
{
	glsl2cpp::vec4i vDefault;
	EXPECT_EQ(vDefault.x, 0);
	EXPECT_EQ(vDefault.y, 0);
	EXPECT_EQ(vDefault.z, 0);
	EXPECT_EQ(vDefault.w, 0);

	glsl2cpp::vec4i vScalar(1);
	EXPECT_EQ(vScalar.x, 1);
	EXPECT_EQ(vScalar.y, 1);
	EXPECT_EQ(vScalar.z, 1);
	EXPECT_EQ(vScalar.w, 1);

	glsl2cpp::vec4i vScalars(2, 3, 4, 5);
	EXPECT_EQ(vScalars.x, 2);
	EXPECT_EQ(vScalars.y, 3);
	EXPECT_EQ(vScalars.z, 4);
	EXPECT_EQ(vScalars.w, 5);

	glsl2cpp::vec4i vCopy(vScalars);
	EXPECT_EQ(vCopy.x, 2);
	EXPECT_EQ(vCopy.y, 3);
	EXPECT_EQ(vCopy.z, 4);
	EXPECT_EQ(vCopy.w, 5);

	glsl2cpp::vec4i vMix(glsl2cpp::vec2i{ 4 }, glsl2cpp::vec2i{ 5 });
	EXPECT_EQ(vMix.x, 4);
	EXPECT_EQ(vMix.y, 4);
	EXPECT_EQ(vMix.z, 5);
	EXPECT_EQ(vMix.w, 5);

	glsl2cpp::vec4i vSwizzlerMix(vMix.xz, vMix.wy);
	EXPECT_EQ(vSwizzlerMix.x, 4);
	EXPECT_EQ(vSwizzlerMix.y, 5);
	EXPECT_EQ(vSwizzlerMix.z, 5);
	EXPECT_EQ(vSwizzlerMix.w, 4);
}

#if ALLOW_GLSL2CPP_NARROW_CONVERSION
TEST(Vector, NarrowConstruction)
{
	glsl2cpp::vec3i vFloatIntoInt(1.f);
	EXPECT_EQ(vFloatIntoInt.x, 1);
	EXPECT_EQ(vFloatIntoInt.y, 1);
	EXPECT_EQ(vFloatIntoInt.z, 1);

	glsl2cpp::vec3f vIntIntoFloat(2, 3, 4);
	EXPECT_EQ(vIntIntoFloat.x, 2);
	EXPECT_EQ(vIntIntoFloat.y, 3);
	EXPECT_EQ(vIntIntoFloat.z, 4);

	glsl2cpp::vec3i vIntFromFloat(vIntIntoFloat);
	EXPECT_EQ(vIntFromFloat.x, 2);
	EXPECT_EQ(vIntFromFloat.y, 3);
	EXPECT_EQ(vIntFromFloat.z, 4);

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
	vIntIntoFloat = vIntFromFloat;

	EXPECT_EQ(vIntIntoFloat, vIntFromFloat);
#endif
}
#endif

double booDouble(const glsl2cpp::mat3d& v)
{
    return v[0][0];
}

TEST(Matrix, Construction)
{
	glsl2cpp::mat3f mat3x3;
	EXPECT_EQ(mat3x3.myData[0], 0);

	glsl2cpp::mat3f mat3x3Identity(1.f);
	EXPECT_EQ(mat3x3Identity.myMat[0][0], 1);
	EXPECT_EQ(mat3x3Identity.myMat[1][1], 1);
	EXPECT_EQ(mat3x3Identity.myMat[2][2], 1);
	EXPECT_EQ(mat3x3Identity.myMat[1][2], 0);

	glsl2cpp::vec3f vX{ 1.f, 2.f, 3.f };
#if ALLOW_GLSL2CPP_NARROW_CONVERSION
	glsl2cpp::vec3i vY{ 4, 5, 6 };
#else
    glsl2cpp::vec3f vY{ 4.f, 5.f, 6.f };
#endif
	glsl2cpp::vec3f vZ{ 7.f, 8.f, 9.f };
	glsl2cpp::mat3f mat3x3Vectors(vX, vY, vZ);
	EXPECT_EQ(mat3x3Vectors.myVec[0], vX);
	EXPECT_EQ(mat3x3Vectors.myVec[1], vY);
	EXPECT_EQ(mat3x3Vectors.myVec[2], vZ);

	glsl2cpp::mat3f mat3x3Copy{ mat3x3Identity };
	EXPECT_EQ(mat3x3Copy.myMat[0][0], 1);
	EXPECT_EQ(mat3x3Copy.myMat[1][1], 1);
	EXPECT_EQ(mat3x3Copy.myMat[2][2], 1);
	EXPECT_EQ(mat3x3Copy.myMat[1][2], 0);

	glsl2cpp::mat4f mat4x4Identity(1.f);
	EXPECT_EQ(mat4x4Identity.myMat[0][0], 1);
	EXPECT_EQ(mat4x4Identity.myMat[1][1], 1);
	EXPECT_EQ(mat4x4Identity.myMat[2][2], 1);
	EXPECT_EQ(mat4x4Identity.myMat[3][3], 1);
	EXPECT_EQ(mat4x4Identity.myMat[3][2], 0);

	EXPECT_EQ(mat4x4Identity.myMat3x3, mat3x3Identity);

	auto result = vX * mat3x3Identity;
	EXPECT_EQ(result, vX);
	EXPECT_EQ(vX * mat3x3Identity, mat3x3Identity * vX);

	result = vX * mat3x3Vectors;
	{
		glsl2cpp::vec3f expected{ 14.f, 32.f, 50.f };
		EXPECT_EQ(result, expected);
	}

	result = mat3x3Vectors * vX;
	{
		glsl2cpp::vec3f expected{ 30.f, 36.f, 42.f };
		EXPECT_EQ(result, expected);
	}

	auto resultMat = mat3x3Vectors * mat3x3Identity;
	EXPECT_EQ(resultMat, mat3x3Vectors);
	EXPECT_EQ(mat3x3Vectors * mat3x3Identity, mat3x3Identity * mat3x3Vectors);

	resultMat = mat3x3Vectors * mat3x3Vectors;
	{
#if ALLOW_GLSL2CPP_NARROW_CONVERSION
		glsl2cpp::mat3f expected{ 30, 36.f, 42.0, 66.0, 81, 96.f, 102.f, 126.0, 150 };
#else
        glsl2cpp::mat3f expected{ 30.f, 36.f, 42.f, 66.f, 81.f, 96.f, 102.f, 126.f, 150.f };
#endif
		EXPECT_EQ(resultMat, expected);
	}

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
    EXPECT_EQ(booDouble(mat3x3Identity), 1);
#else
    EXPECT_EQ(booDouble(glsl2cpp::mat3d{ mat3x3Identity }), 1);
#endif
}

double fooDouble(const glsl2cpp::vec3d& v)
{
	return v.x;
}

TEST(Vector, ImplicitConversion)
{
	glsl2cpp::vec3d vDouble(1.0);
	glsl2cpp::vec3f vFloat(2.f);

	EXPECT_EQ(fooDouble(glsl2cpp::vec3d{ vFloat }), 2);
#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
	EXPECT_EQ(fooDouble(vFloat), 2);
#endif
}

TEST(Vector, Assignment)
{
	glsl2cpp::vec3i vOne(1);
	glsl2cpp::vec3i vTwo(2);

	vOne = vTwo;
	EXPECT_EQ(vOne.x, 2);
	EXPECT_EQ(vOne.y, 2);
	EXPECT_EQ(vOne.z, 2);

	glsl2cpp::vec3l vThree(3);

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
	vThree = vOne;
	EXPECT_EQ(vThree.x, 2);
	EXPECT_EQ(vThree.y, 2);
	EXPECT_EQ(vThree.z, 2);

#if ALLOW_GLSL2CPP_NARROW_CONVERSION
	vThree = vTwo;
	EXPECT_EQ(vThree.x, 2);
	EXPECT_EQ(vThree.y, 2);
	EXPECT_EQ(vThree.z, 2);

	glsl2cpp::vec3f vFour(4.f);

	vOne = vFour;
	EXPECT_EQ(vOne.x, 4);
	EXPECT_EQ(vOne.y, 4);
	EXPECT_EQ(vOne.z, 4);
#endif
#endif
}

TEST(Vector, SwizzlerAssignment)
{
	glsl2cpp::vec3i vOne(1);
	glsl2cpp::vec3i vTwo(2);

	vOne.y = 3;
	vTwo.y = 4;

	vOne.xz = vTwo.xy;
	EXPECT_EQ(vOne.x, 2);
	EXPECT_EQ(vOne.y, 3);
	EXPECT_EQ(vOne.z, 4);

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION

	glsl2cpp::vec3l vThree(3);

	vThree.zy = vOne.zz;
	EXPECT_EQ(vThree.x, 3);
	EXPECT_EQ(vThree.y, 4);
	EXPECT_EQ(vThree.z, 4);

	vThree = vOne.xxz;
	EXPECT_EQ(vThree.x, 2);
	EXPECT_EQ(vThree.y, 2);
	EXPECT_EQ(vThree.z, 4);

#if ALLOW_GLSL2CPP_NARROW_CONVERSION
	vOne.xy = vThree.zz;
	EXPECT_EQ(vOne.x, 4);
	EXPECT_EQ(vOne.y, 4);
	EXPECT_EQ(vOne.z, 4);

	glsl2cpp::vec3f vFour(4.f, 5.f, 6.f);

	vOne.zyx = vFour.yyz;
	EXPECT_EQ(vOne.x, 6);
	EXPECT_EQ(vOne.y, 5);
	EXPECT_EQ(vOne.z, 5);

	vOne = vFour.zyx;
	EXPECT_EQ(vOne.x, 6);
	EXPECT_EQ(vOne.y, 5);
	EXPECT_EQ(vOne.z, 4);
#endif
#endif
}

TEST(Vector, Addition)
{
	glsl2cpp::vec3i vOne(1);
	glsl2cpp::vec3i vTwo(2);

	auto vThree = vOne + vTwo;
	EXPECT_EQ(vThree.x, 3);
	EXPECT_EQ(vThree.y, 3);
	EXPECT_EQ(vThree.z, 3);

	vOne += vThree;
	EXPECT_EQ(vOne.x, 4);
	EXPECT_EQ(vOne.y, 4);
	EXPECT_EQ(vOne.z, 4);

	glsl2cpp::vec3l vFour(4);

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION
	vFour += vOne;
	EXPECT_EQ(vFour.x, 8);
	EXPECT_EQ(vFour.y, 8);
	EXPECT_EQ(vFour.z, 8);

	vFour = vOne + vTwo;
	EXPECT_EQ(vFour.x, 6);
	EXPECT_EQ(vFour.y, 6);
	EXPECT_EQ(vFour.z, 6);

	glsl2cpp::vec3l::scalar_type valBig = std::numeric_limits<int>::max() + 20ll;
	glsl2cpp::vec3l vBig(valBig);

	valBig += 2;
	vFour = vBig + vTwo;
	EXPECT_EQ(vFour.x, valBig);
	EXPECT_EQ(vFour.y, valBig);
	EXPECT_EQ(vFour.z, valBig);

	vFour = vTwo + vBig;
	EXPECT_EQ(vFour.x, valBig);
	EXPECT_EQ(vFour.y, valBig);
	EXPECT_EQ(vFour.z, valBig);

	vFour = vTwo.xxx + vBig.yyy;
	EXPECT_EQ(vFour.x, valBig);
	EXPECT_EQ(vFour.y, valBig);
	EXPECT_EQ(vFour.z, valBig);

	vFour = vOne;
	vFour.xy += vOne.zy;
	EXPECT_EQ(vFour.x, 8);
	EXPECT_EQ(vFour.y, 8);
	EXPECT_EQ(vFour.z, 4);

	auto vSix = vOne + vFour;
	auto vSeven = vFour + vOne;
	EXPECT_EQ(vSix, vSeven);

#endif
}

TEST(Vector, Difference)
{
	glsl2cpp::vec3i vOne(1);
	glsl2cpp::vec3i vTwo(2);

	auto vThree = vTwo - vOne;
	EXPECT_EQ(vThree.x, 1);
	EXPECT_EQ(vThree.y, 1);
	EXPECT_EQ(vThree.z, 1);

	vOne -= vThree;
	EXPECT_EQ(vOne.x, 0);
	EXPECT_EQ(vOne.y, 0);
	EXPECT_EQ(vOne.z, 0);

	glsl2cpp::vec3l vFour(4);

#if ALLOW_GLSL2CPP_IMPLICIT_CONVERSION

	vFour -= vOne;
	EXPECT_EQ(vFour.x, 4);
	EXPECT_EQ(vFour.y, 4);
	EXPECT_EQ(vFour.z, 4);

	vFour = vOne - vTwo;
	EXPECT_EQ(vFour.x, -2);
	EXPECT_EQ(vFour.y, -2);
	EXPECT_EQ(vFour.z, -2);

	glsl2cpp::vec3l::scalar_type valBig = -std::numeric_limits<int>::max() - 20ll;
	glsl2cpp::vec3l vBig(valBig);

	valBig -= 2;
	vFour = vBig - vTwo;
	EXPECT_EQ(vFour.x, valBig);
	EXPECT_EQ(vFour.y, valBig);
	EXPECT_EQ(vFour.z, valBig);

	vFour = vTwo - vBig;
	EXPECT_EQ(vFour.x, -valBig);
	EXPECT_EQ(vFour.y, -valBig);
	EXPECT_EQ(vFour.z, -valBig);

	vFour = vBig.yyy - vTwo.xxx;
	EXPECT_EQ(vFour.x, valBig);
	EXPECT_EQ(vFour.y, valBig);
	EXPECT_EQ(vFour.z, valBig);

	vFour = vTwo;
	vFour.xy -= vTwo.zy;
	EXPECT_EQ(vFour.x, 0);
	EXPECT_EQ(vFour.y, 0);
	EXPECT_EQ(vFour.z, 2);

	auto vSix = vOne - vFour;
	auto vSeven = vFour - vOne;
	EXPECT_EQ(vSix.xy, vSeven.yx);
#endif
}

TEST(Vector, Function)
{
	glsl2cpp::vec3f v(2.f, 4.f, 8.f);
	glsl2cpp::vec3f e(1.f, 2.f, 3.f);

    auto r = log2(v);

	EXPECT_EQ(r, e);

	glsl2cpp::vec3f exp(3.f, 2.f, 1.f);
	glsl2cpp::vec3f expected(8.f, 16.f, 8.f);

    r = pow(v, exp.xyz);

	EXPECT_EQ(r, expected);

	glsl2cpp::vec3f one(1.f, 1.f, 1.f);
    r = pow(v, 0);

	EXPECT_EQ(r, one);

	glsl2cpp::vec3f max(3.f, 4.5f, 5.f);
	glsl2cpp::vec3f clamp(2.f, 4.f, 5.f);

    r = Clamp(v, 2.f, max);

	EXPECT_EQ(r, clamp);
}

class Oracle
{
public:
    static size_t num_of_oracles;

    Oracle() : value{++num_of_oracles} {}

    Oracle(int i) : value(i) {
        ++num_of_oracles;
    }

    ~Oracle()
    {
        --num_of_oracles;
    }

    size_t value;
};

size_t Oracle::num_of_oracles = 0;

int fooUnique(std::unique_ptr<Oracle> anOracle, int aVal) {
    return (anOracle ? anOracle->value : Oracle::num_of_oracles) + aVal;
}

TEST(Vector, NonScalarTypes)
{
    using oracle_unique = std::unique_ptr<Oracle>;
    using unique_ptr_vec_3 = glsl2cpp::Vector<oracle_unique, 3>;

    Oracle::num_of_oracles = 0;

    ASSERT_EQ(Oracle::num_of_oracles, 0);

    unique_ptr_vec_3 v { std::make_unique<Oracle>(1), std::make_unique<Oracle>(2) , std::make_unique<Oracle>(3) };

    ASSERT_EQ(Oracle::num_of_oracles, 3);
    EXPECT_EQ(v[0]->value, 1);
    EXPECT_EQ(v[1]->value, 2);
    EXPECT_EQ(v[2]->value, 3);

    {
        unique_ptr_vec_3 u{ std::move(v) };

        EXPECT_FALSE(v[0]);
        EXPECT_FALSE(v[1]);
        EXPECT_FALSE(v[2]);

        ASSERT_EQ(Oracle::num_of_oracles, 3);
        EXPECT_EQ(u[0]->value, 1);
        EXPECT_EQ(u[1]->value, 2);
        EXPECT_EQ(u[2]->value, 3);
    }

    ASSERT_EQ(Oracle::num_of_oracles, 0);

    using oracle_vec3 = glsl2cpp::Vector<Oracle, 3>;
    oracle_vec3 u{};

    EXPECT_EQ(u[0].value, 1);
    EXPECT_EQ(u[1].value, 2);
    EXPECT_EQ(u[2].value, 3);

    unique_ptr_vec_3 w{ std::make_unique<Oracle>(1), std::make_unique<Oracle>(2) , std::make_unique<Oracle>(3) };
    int i = 1;
    auto r = vec_invoke([](auto&&... someArgs) { return fooUnique(std::forward<decltype(someArgs)>(someArgs)...); }, std::move(w), i);

    EXPECT_EQ(r[0], 4);
    EXPECT_EQ(r[1], 3);
    EXPECT_EQ(r[2], 2);
}
