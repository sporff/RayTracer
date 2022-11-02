
#include <cmath>
#include <algorithm>
#include "Ray.h"
#include "IWorldObject.h"

using namespace RayTracer;

IWorldObject::IWorldObject()
{ }

IWorldObject::~IWorldObject()
{ }

bool IWorldObject::GetRayIntersection(const Ray& pRay, float* pT_OUT, Vector3f* pIntersect_OUT)
{
	return false;
}

bool IWorldObject::DoesRayIntersectAABB(const Vector3f& center, const Vector3f& radius, const Ray& ray, Vector3f* pIntersect_OUT)
{
	Vector3f cornerVec = Vector3f(radius.x, radius.y, radius.z);
	Vector3f lb = center - cornerVec;
	Vector3f rt = center + cornerVec;
	Vector3f dirfrac;
	Vector3f rayStart = ray.GetStart();
	Vector3f unitRay = ray.GetDirection().FastNormalize();

	// r.dir is unit direction vector of ray
	dirfrac.x = 1.0f / unitRay.x;
	dirfrac.y = 1.0f / unitRay.y;
	dirfrac.z = 1.0f / unitRay.z;

	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (lb.x - rayStart.x) * dirfrac.x;
	float t2 = (rt.x - rayStart.x) * dirfrac.x;
	float t3 = (lb.y - rayStart.y) * dirfrac.y;
	float t4 = (rt.y - rayStart.y) * dirfrac.y;
	float t5 = (lb.z - rayStart.z) * dirfrac.z;
	float t6 = (rt.z - rayStart.z) * dirfrac.z;

	float t;
	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;

	// I have no idea if this is correct
	if (pIntersect_OUT != nullptr)
	{
		*pIntersect_OUT = rayStart + (unitRay*t);
	}
	return true;
}

/*
	Vector3f cornerVec = Vector3f(m_radius, m_radius, m_radius);
	Vector3f lb = m_position - cornerVec;
	Vector3f rt = m_position + cornerVec;
	Vector3f dirfrac;
	Vector3f rayStart = ray.GetStart();
	Vector3f unitRay = ray.GetDirection().FastNormalize();

	// r.dir is unit direction vector of ray
	dirfrac.x = 1.0f / unitRay.x;
	dirfrac.y = 1.0f / unitRay.y;
	dirfrac.z = 1.0f / unitRay.z;

	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (lb.x - rayStart.x) * dirfrac.x;
	float t2 = (rt.x - rayStart.x) * dirfrac.x;
	float t3 = (lb.y - rayStart.y) * dirfrac.y;
	float t4 = (rt.y - rayStart.y) * dirfrac.y;
	float t5 = (lb.z - rayStart.z) * dirfrac.z;
	float t6 = (rt.z - rayStart.z) * dirfrac.z;

	float t;
	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
*/