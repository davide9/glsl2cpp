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
}
#endif