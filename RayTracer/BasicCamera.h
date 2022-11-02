#pragma once
#include "ICamera.h"
#include "IRotator.h"
#include "TaskExecutor.h"

namespace RayTracer
{

class BasicCamera : public ICamera
{
public:
	BasicCamera();
	virtual ~BasicCamera();

private:
	std::shared_ptr<IRotator> m_orientation;
};

}
