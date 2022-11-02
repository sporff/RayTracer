#include "Vector3f.h"
#include "Ray.h"
#include "IWorldObject.h"
#include "Cuboid.h"

using namespace RayTracer;

RayTracer::Cuboid::Cuboid()
{
}

RayTracer::Cuboid::Cuboid(Vector3f position, Vector3f radius)
{
	m_position = position;
	m_radius = radius;
}

RayTracer::Cuboid::~Cuboid()
{
}

bool Cuboid::GetRayIntersection(const Ray& ray, float* pT_OUT, Vector3f* pIntersect_OUT)
{
	return IWorldObject::DoesRayIntersectAABB(m_position, m_radius, ray, pIntersect_OUT);
	//return false;
}