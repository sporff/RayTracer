#include "IRotator.h"

using namespace RayTracer;

IRotator::IRotator()
{

}

IRotator::~IRotator()
{

}

RayTracer::Vector3f IRotator::RotateVector(const Vector3f& v)
{
	return Vector3f::Zero();
}
