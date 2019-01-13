#include "pch.h"

#include <Vector.h>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

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

#if ALLOW_GLSL2CPP_VECTOR_NARROW_CONVERSION
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

	vIntIntoFloat = vIntFromFloat;
}
#endif

TEST(Vector, Assignment)
{
	glsl2cpp::vec3i vOne(1);
	glsl2cpp::vec3i vTwo(2);

	vOne = vTwo;
	EXPECT_EQ(vOne.x, 2);
	EXPECT_EQ(vOne.y, 2);
	EXPECT_EQ(vOne.z, 2);

	glsl2cpp::vec3l vThree(3);

	vThree = vOne;
	EXPECT_EQ(vThree.x, 2);
	EXPECT_EQ(vThree.y, 2);
	EXPECT_EQ(vThree.z, 2);

#if ALLOW_GLSL2CPP_VECTOR_NARROW_CONVERSION
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

	glsl2cpp::vec3l vThree(3);

	vThree.zy = vOne.zz;
	EXPECT_EQ(vThree.x, 3);
	EXPECT_EQ(vThree.y, 4);
	EXPECT_EQ(vThree.z, 4);

	vThree = vOne.xxz;
	EXPECT_EQ(vThree.x, 2);
	EXPECT_EQ(vThree.y, 2);
	EXPECT_EQ(vThree.z, 4);

#if ALLOW_GLSL2CPP_VECTOR_NARROW_CONVERSION
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
}

TEST(Vector, Invoke)
{
	glsl2cpp::vec3f v(2.f, 4.f, 8.f);
	glsl2cpp::vec3f e(1.f, 2.f, 3.f);

	auto r = v.Invoke([](auto v) { return std::log2(v); });

	EXPECT_EQ(r, e);

	glsl2cpp::vec3f exp(3.f, 2.f, 1.f);
	glsl2cpp::vec3f expected(8.f, 16.f, 8.f);

	r = v.Invoke([](auto base, auto exp) { return std::pow(base, exp); }, exp.xyz);

	EXPECT_EQ(r, expected);

	glsl2cpp::vec3f one(1.f, 1.f, 1.f);
	r = v.Invoke([](auto base, auto exp) { return std::pow(base, exp); }, 0);

	EXPECT_EQ(r, one);

	glsl2cpp::vec3f max(3.f, 4.5f, 5.f);
	glsl2cpp::vec3f clamp(2.f, 4.f, 5.f);
	r = v.Invoke([](auto v, auto min, auto max) { return v < min ? min : v > max ? max : v; }, 2.f, max);

	EXPECT_EQ(r, clamp);
}