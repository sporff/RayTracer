#pragma once

#include <SFML/Graphics.hpp>
#include "Vector3f.h"
#include "QuatRotator.h"
#include "TaskExecutor.h"

namespace RayTracer
{

class IObjectManager;

class ICamera
{
public:
	ICamera();
	virtual ~ICamera() = 0;

	void SetPosition(const Vector3f& pos);
	void AddToPosition(const Vector3f& v);
	Vector3f GetPosition();

	void AddToOrientation(QuatRotator qr);
	QuatRotator GetOrientation();

protected:
	Vector3f m_position;
	QuatRotator m_orientation;
};

}