#pragma once
#include "GraphicsWrapper.h"
#include "IObjectManager.h"
#include "ICamera.h"
#include "Sphere.h"
#include "TaskExecutor.h"

#define RADTODEG(r) ((float)r*360) / (2.f*3.14159f)
#define DEGTORAD(d) ((float)d*2.f*3.14159f) / 360.f

namespace RayTracer
{

class RayTracerApp
{
public:
	RayTracerApp();
	~RayTracerApp();

	bool Execute();

private:
	GraphicsWrapper m_graphicsWrapper;
	IObjectManager* m_pObjectManager;
	ICamera* m_camera;

	TaskExecutor m_taskExec;
};

}