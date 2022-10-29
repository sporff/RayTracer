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

Vector3f RayTracer::QuatRotator::RotateVector(const Vector3f& v)
{
	return Vector3f::Zero();
	return q * v;
}
