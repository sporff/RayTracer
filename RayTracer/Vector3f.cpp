#include <iostream>
#include <cmath>
#include "Vector3f.h"

using namespace RayTracer;

Vector3f::Vector3f()
	: x(0.f)
	, y(0.f)
	, z(0.f)
{ }

Vector3f::Vector3f(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{ }

Vector3f::Vector3f(const Vector3f& copyFrom)
	: x(copyFrom.x)
	, y(copyFrom.y)
	, z(copyFrom.z)
{ }

Vector3f::~Vector3f()
{ }

float Vector3f::Length() const
{
	return std::sqrt(x*x + y*y + z*z);
}

float Vector3f::LengthSquared() const
{
	return x*x + y*y + z*z;
}


float Vector3f::FastInverseLength() const
{
	float x = LengthSquared();
	float xhalf = 0.5f * x;
	int i = *(int*)&x;            // store floating-point bits in integer
	i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
	x = *(float*)&i;              // convert new bits into float
	x = x * (1.5f - xhalf * x * x);     // One round of Newton's method
	return x;
}


Vector3f Vector3f::Normalize() const
{
	float inverseLen = 1.f / Length();
	return Vector3f(x*inverseLen, y*inverseLen, z*inverseLen);
}

Vector3f Vector3f::FastNormalize() const
{
	//return *this * FastInverseLength();
	float inverseLen = FastInverseLength();
	return Vector3f(x * inverseLen, y * inverseLen, z * inverseLen);
}

float Vector3f::Dot(const Vector3f& v2) const
{
	return x*v2.x + y*v2.y + z*v2.z;
}

Vector3f Vector3f::Cross(const Vector3f& v2) const
{
	return Vector3f(
		y*v2.z - z*v2.y,
		z*v2.x - x*v2.z,
		x*v2.y - y*v2.x
	);
}

Vector3f Vector3f::Scale(float scalar) const
{
	return Vector3f(x*scalar, y*scalar, z*scalar);
}

Vector3f Vector3f::operator*(float scalar) const
{
	return Scale(scalar);
}

Vector3f Vector3f::operator-(const Vector3f& rhs) const
{
	return Vector3f(x-rhs.x, y-rhs.y, z-rhs.z);
}


Vector3f Vector3f::operator+(const Vector3f& rhs) const
{
	return Vector3f(x+rhs.x, y+rhs.y, z+rhs.z);
}

Vector3f Vector3f::operator+=(const Vector3f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

void Vector3f::Print()
{
	std::cout << x << "," << y << "," << z << "\n";
	//std::cout << "FVector(" << x << "," << y << "," << z << ")\n";
}

Vector3f Vector3f::Zero()
{
	return Vector3f(0.f, 0.f, 0.f);
}
