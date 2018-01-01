#pragma once

#include <Windows.h>
#include <DirectXMath.h>
#include <random>

class MathHelper
{
public:
	// Returns random float in [0, 1).
	static float Rand()
	{
		return std::uniform_real_distribution<float>{0.0f, 1.0f}(Generator);
	}

	// Returns random float in [a, b).
	static float Rand(float a, float b)
	{
		return std::uniform_real_distribution<float>{a, b}(Generator);
	}

	static int Rand(int a, int b)
	{
		return std::uniform_int_distribution<int>{ a, b }(Generator);
	}

	template <typename T>
	static auto Min(T&& a, T&& b)
	{
		return std::min(a, b);
	}

	template <typename T>
	static auto Max(T&& a, T&& b)
	{
		return std::max(a, b);
	}

	template <typename T>
	static auto Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a)*t;
	}

	template <typename T>
	static auto Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}

	static float AngleFromXY(float x, float y);

	static DirectX::XMVECTOR SphericalToCartesian(float radius, float theta, float phi)
	{
		return DirectX::XMVectorSet(
			radius*sinf(phi)*cosf(theta),
			radius*cosf(phi),
			radius*sinf(phi)*sinf(theta),
			1.0f);
	}

	static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M)
	{
		// Inverse-transpose is just appliet to normals. So zero out
		// translation row so that it doesn't get into inverse-transpose
		// calculation--we don't want the inverse-transpose of translation.
		DirectX::XMMATRIX A = M;
		A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, A));
	}

	static DirectX::XMFLOAT4X4 Identity4x4()
	{
		return DirectX::XMFLOAT4X4{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	static DirectX::XMVECTOR RandUnitVec3();
	static DirectX::XMVECTOR RandHemisphereUnitVec3(DirectX::XMVECTOR n);

	// Access to the generator.
	static std::mt19937& GetGenerator() { return MathHelper::Generator; };

	static const float Infinity;
	static const float Pi;
private:
	static std::mt19937 Generator;
};