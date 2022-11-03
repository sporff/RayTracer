#include "EulerRotator.h"
#include "QuatRotator.h"

using namespace RayTracer;

EulerRotator::EulerRotator()
{

}

EulerRotator::~EulerRotator()
{

}

void RayTracer::EulerRotator::Set(float xAngle, float yAngle, float zAngle)
{
	m_xAngle = xAngle;
	m_yAngle = yAngle;
	m_zAngle = zAngle;
}

Vector3f RayTracer::EulerRotator::RotateVector(const Vector3f& v)
{
	// TODO
	return Vector3f::Zero();
}
