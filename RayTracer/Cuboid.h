#pragma once

#include <memory>

#include "Vector3f.h"
#include "IRotator.h"
#include "IWorldObject.h"

namespace RayTracer
{

class Cuboid : public IWorldObject
{
public:
	Cuboid();
	Cuboid(Vector3f position, Vector3f radius);
	virtual ~Cuboid();

	virtual bool GetRayIntersection(const Ray& ray, float* pT_OUT, Vector3f* pIntersect_OUT = nullptr) override;

private:
	Vector3f m_position;
	Vector3f m_radius;
	std::shared_ptr<IRotator> m_pRotator;	// Ignored for now
};

}