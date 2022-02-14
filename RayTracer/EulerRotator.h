#pragma once
#include "IRotator.h"

namespace RayTracer
{
    class EulerRotator : public IRotator
    {
    public:
        EulerRotator();
        virtual ~EulerRotator();

        virtual Vector3f RotateVector(const Vector3f& v);
    };

}

