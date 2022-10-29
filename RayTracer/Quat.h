#pragma once

#include "Vector3f.h"

namespace RayTracer
{

class Quat
{
public:
	Quat();
	Quat(float X, float Y, float Z, float W);

	void Set(const Quat& q);
	void Set(float X, float Y, float Z, float W);
	void Set(const Vector3f& vec);

	bool Equals(const Quat& from) const;
	Quat Multiply(const Quat& B) const;
	Vector3f Multiply(const Vector3f& B) const;

	Quat operator*(const Quat& B) const;
	Quat operator*=(const Quat& B);
	Vector3f operator*(const Vector3f& B) const;

	Quat& operator=(const Quat& from);

	bool operator==(const Quat& B) const;

private:
	float X, Y, Z, W;
};

}

