#pragma once
#include "IWorldObject.h"

namespace RayTracer
{

class Sphere : public IWorldObject
{
public:
    Sphere();
    Sphere(Vector3f position, float radius);
    virtual ~Sphere();

    bool GetRayIntersection(const Ray& ray, float* pT_OUT, Vector3f* pIntersect_OUT=nullptr) override;

    bool DoesRayIntersectAABB(const Ray& ray);
    bool DoesRayIntersectAABB2(const Ray& ray);

private:

    Vector3f m_position;
    float m_radius;
};

}