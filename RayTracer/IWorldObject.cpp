#include "Ray.h"
#include "IWorldObject.h"

using namespace RayTracer;

IWorldObject::IWorldObject()
{ }

IWorldObject::~IWorldObject()
{ }

bool IWorldObject::GetRayIntersection(const Ray& pRay, float* pT_OUT, Vector3f* pIntersect_OUT)
{ return false; }
