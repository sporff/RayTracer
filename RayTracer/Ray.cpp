#include "Ray.h"
#include <cmath>

using namespace RayTracer;

Ray::Ray()
{ }

Ray::Ray(Vector3f start, Vector3f direction)
	: m_start(start)
	, m_direction(direction)
{ }

Ray::~Ray()
{ }

float Ray::Length()
{
	return m_direction.Length();
}

float Ray::LengthSquared()
{
	return m_direction.LengthSquared();
}

RayTracer::Vector3f Ray::GetStart() const
{
	return m_start;
}

RayTracer::Vector3f Ray::GetDirection() const
{
	return m_direction;
}

void Ray::SetStart(const Vector3f& v)
{
	m_start = v;
}

void Ray::SetDirection(const Vector3f& v)
{
	m_direction = v;
}
