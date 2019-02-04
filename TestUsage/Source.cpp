#include <Vector.h>

using namespace glsl2cpp;

bool testVec(float aVal0, float aVal1, float aVal2, float aVal3, float aVal4)
{
	vec2f v0(aVal0, aVal2);
	vec2f v1(aVal1, aVal3);

	auto vR = dot(v0, v1);

	return vR == aVal4;
}

bool testNoVec(float aVal0, float aVal1, float aVal2, float aVal3, float aVal4)
{
	auto vR = aVal0 * aVal1 + aVal2 * aVal3;

	return vR == aVal4;
}

int main(int argc, char* argv[])
{
	auto cos30 = sqrtf(3.f) / 2.f;

	bool tNV = testNoVec(cos30, .5f, .5f, cos30, cos30);
	bool tV = testVec(cos30, cos30, .5f, cos30, cos30);

	vec3d x(1., 0., 0.);
	vec3f y(0.f, 1.f, 0.f);
	vec3d z(0., 0., 1.);

	auto l = length(x);
	auto lf = length(y);
	if (l > lf)
	{
		return 3;
	}

	if (cross(x, y) == z)
	{
		return 2;
	}

	if (tV == tNV)
	{
		return 0;
	}
	return 1;
}