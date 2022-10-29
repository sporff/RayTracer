#pragma once

#include "Vector3f.h"

namespace RayTracer
{

class Quat
{
public:
	Quat();
	Quat(float X, float Y, float Z, float W);

	void Set(float X, float Y, float Z, float W);
	void Set(const Vector3f& vec);

	bool Equals(const Quat& from) const;
	Quat Multiply(const Quat& B) const;

	Quat operator*(const Quat& B) const;
	Quat& operator=(const Quat& from);
	bool operator==(const Quat& B) const;

private:
	float X, Y, Z, W;
};

}

