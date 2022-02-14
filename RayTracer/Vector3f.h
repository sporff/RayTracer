#pragma once
#include <SFML/System/Vector2.hpp>

namespace RayTracer
{

class Vector3f
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& copyFrom);
	~Vector3f();

	static Vector3f Zero();

	float Length() const;
	float LengthSquared() const;
	float FastInverseLength() const;
	Vector3f Normalize() const;
	Vector3f FastNormalize() const;
	float Dot(const Vector3f& v2) const;
	Vector3f Cross(const Vector3f& v2) const;

	Vector3f Scale(float scalar) const;
	Vector3f operator*(float scalar) const;
	Vector3f operator-(const Vector3f& rhs) const;
	Vector3f operator+(const Vector3f& rhs) const;
	Vector3f operator+=(const Vector3f& rhs);

	void Print();

	float x, y, z;
};

}
