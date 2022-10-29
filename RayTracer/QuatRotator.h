#pragma once
#include "IRotator.h"
#include "Quat.h"

namespace RayTracer
{

class QuatRotator : public IRotator
{
public:
	QuatRotator();
	QuatRotator(const Quat& q);
	virtual ~QuatRotator();

	void Set(const Quat& q);

	virtual Vector3f RotateVector(const Vector3f& v);


private:
	Quat q;
};

}