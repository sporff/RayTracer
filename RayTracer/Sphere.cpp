#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>
#include "Sphere.h"

using namespace RayTracer;

Sphere::Sphere()
	: m_position()
{

}

Sphere::Sphere(Vector3f position, float radius)
	: m_position(position)
	, m_radius(radius)
{

}

Sphere::~Sphere()
{

}

bool Sphere::GetRayIntersection(const Ray& ray, float* pT_OUT, Vector3f* pIntersect_OUT)
{
	/*if (!DoesRayIntersectAABB(ray))
	{
		return false;
	}
	else
	{
		*pIntersect_OUT = Vector3f(100, 100, 100);
		return true;
	}*/

	Vector3f rayVec = ray.GetDirection();
	Vector3f d = rayVec.Normalize();
	Vector3f m = (ray.GetStart() - m_position);

	float b = m.Dot(d);
	float c = m.Dot(m) - m_radius*m_radius;

	if (c > 0.f && b > 0.f)
		return false;

	float discr = b*b - c;
	if (discr < 0.f)
		return false;

	float t = -b - std::sqrt(discr);

	if (t < 0.f)
		t = 0.f;

	if (pT_OUT != nullptr)
	{
		*pT_OUT = t;
	}
	if (pIntersect_OUT != nullptr)
	{
		*pIntersect_OUT = ray.GetStart() + d*t;
	}

	return true;
}


/*
// Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
// returns t value of intersection and intersection point q
int IntersectRaySphere(Point p, Vector d, Sphere s, float& t, Point& q)
{
	Vector m = p - s.c;
	float b = Dot(m, d);
	float c = Dot(m, m) - s.r * s.r;

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f) return 0;
	float discr = b * b - c;

	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0f) return 0;

	// Ray now found to intersect sphere, compute smallest t value of intersection
	t = -b - Sqrt(discr);

	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0f) t = 0.0f;
	q = p + t * d;

	return 1;
}
*/

std::atomic<int64_t> agg_one=0, agg_two=0, agg_three=0, agg_four=0;
bool Sphere::DoesRayIntersectAABB(const Ray& ray)
{
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
}

bool Sphere::DoesRayIntersectAABB2(const Ray& ray)
{
	/*Vector3f rayStart = ray.GetStart();
	Vector3f rayEnd = ray.GetEnd();

	double tx1 = (b.min.x - rayStart.x) * r.n_inv.x;
	double tx2 = (b.max.x - rayStart.x) * r.n_inv.x;

	double tmin = min(tx1, tx2);
	double tmax = max(tx1, tx2);

	double ty1 = (b.min.y - rayStart.y) * r.n_inv.y;
	double ty2 = (b.max.y - rayStart.y) * r.n_inv.y;

	tmin = max(tmin, min(ty1, ty2));
	tmax = min(tmax, max(ty1, ty2));

	return tmax >= tmin;*/
	return false;
}
