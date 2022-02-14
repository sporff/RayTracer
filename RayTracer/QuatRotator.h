#pragma once
#include "IRotator.h"

namespace RayTracer
{

	class QuatRotator : public IRotator
	{
	public:
		QuatRotator();
		virtual ~QuatRotator();

		virtual Vector3f RotateVector(const Vector3f& v);
	};

}