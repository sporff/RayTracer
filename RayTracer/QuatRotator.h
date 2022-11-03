#pragma once
#include "IRotator.h"
#include "EulerRotator.h"
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
	void Set(float xAngle, float yAngle, float zAngle);
	Quat GetQuat();

	void AddRotation(const QuatRotator& qr);

	virtual Vector3f RotateVector(const Vector3f& v) override;
	virtual Vector3f RotateVectorInverse(const Vector3f& v) override;


private:
	Quat q;
};

}