#pragma once
#include "Vector3f.h"

namespace RayTracer
{

class Ray
{
public:
	Ray();
	Ray(Vector3f start, Vector3f direction);
	~Ray();

	float Length();
	float LengthSquared();

	void SetStart(const Vector3f& v);
	void SetDirection(const Vector3f& v);

	Vector3f GetStart() const;
	Vector3f GetDirection() const;

protected:
	Vector3f m_start;
	Vector3f m_direction;
};

}