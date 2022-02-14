#pragma once
#include "Ray.h"

namespace RayTracer
{

class IWorldObject
{
public:
	IWorldObject();
	virtual ~IWorldObject() = 0;

	virtual bool GetRayIntersection(const Ray& pRay, float* pT_OUT, Vector3f* pIntersect_OUT=nullptr) = 0;
};

}