#pragma once
#include "IRotator.h"
#include "QuatRotator.h"

namespace RayTracer
{

class EulerRotator : public IRotator
{
public:
    EulerRotator();
    virtual ~EulerRotator();

    void Set(float xAngle, float yAngle, float zAngle);

    virtual Vector3f RotateVector(const Vector3f& v) override;

private:
    float m_xAngle, m_yAngle, m_zAngle;
};

}

