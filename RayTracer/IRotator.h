#pragma once
#include "Vector3f.h"

namespace RayTracer
{

class IRotator
{
public:
	IRotator();
	virtual ~IRotator() = 0;

	virtual Vector3f RotateVector(const Vector3f& v) = 0;
	virtual Vector3f RotateVectorInverse(const Vector3f& v) = 0;
};

}

