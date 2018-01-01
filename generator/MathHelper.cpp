#include "MathHelper.h"
#include <float.h>
#include <cmath>

using namespace DirectX;

const float MathHelper::Infinity = FLT_MAX;
const float MathHelper::Pi = 3.1415926535f;

std::mt19937 MathHelper::Generator = std::mt19937{ std::random_device{}() };

float MathHelper::AngleFromXY(float x, float y)
{
	float theta = 0.0f;

	// Quadrant I or IV
	if (x >= 0.0f)
	{
		theta = atanf(y / x); // in [-pi/2, pi/2]

		if (theta < 0.0f)
			theta += 2.0f * Pi;
	}
	else
		theta = atanf(y / x) + Pi;

	return theta;
}

XMVECTOR MathHelper::RandUnitVec3()
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);

	// keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(MathHelper::Rand(-1.f, 1.f), MathHelper::Rand(-1.f, 1.f), MathHelper::Rand(-1.f, 1.f), 0.0f);

		// Ignore points outside the unit sphere to get an even distribution over the unit sphere.
		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		return XMVector3Normalize(v);
	}
}

XMVECTOR MathHelper::RandHemisphereUnitVec3(XMVECTOR n)
{
	XMVECTOR One = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR Zero = XMVectorZero();

	// keep trying until we get a point on/in the hemisphere.
	while (true)
	{
		// Generate random point in the cube [-1,1]^3.
		XMVECTOR v = XMVectorSet(MathHelper::Rand(-1.f, 1.f), MathHelper::Rand(-1.f, 1.f), MathHelper::Rand(-1.f, 1.f), 0.0f);

		// Ignore points outside the unit sphere to get an even distribution over the unit sphere.
		if (XMVector3Greater(XMVector3LengthSq(v), One))
			continue;

		// Ignore points in the bottom hemisphere.
		if (XMVector3Less(XMVector3Dot(n, v), Zero))
			continue;

		return XMVector3Normalize(v);
	}
}