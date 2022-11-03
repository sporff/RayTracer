#include "EulerRotator.h"
#include "QuatRotator.h"

using namespace RayTracer;

QuatRotator::QuatRotator()
{

}

QuatRotator::QuatRotator(const Quat& q)
{
	Set(q);
}

QuatRotator::~QuatRotator()
{

}

void QuatRotator::Set(const Quat& q)
{
	this->q = q;
}

/*
* Build quat rotator from euler angles
*/
void RayTracer::QuatRotator::Set(float xAngle, float yAngle, float zAngle)
{
	q.Set(xAngle, yAngle, zAngle);
}

Quat RayTracer::QuatRotator::GetQuat()
{
	return q;
}

void RayTracer::QuatRotator::AddRotation(const QuatRotator& qr)
{
	q *= qr.q;
}

Vector3f RayTracer::QuatRotator::RotateVector(const Vector3f& v)
{
	//return Vector3f::Zero();
	return q * v;
}

Vector3f RayTracer::QuatRotator::RotateVectorInverse(const Vector3f& v)
{
	return q.Inverse() * v;
}
