#pragma once
#include "GraphicsWrapper.h"
#include "IRenderer.h"
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
	IRenderer* m_pRenderer;
	IObjectManager* m_pObjectManager;
	ICamera* m_pCamera;

	TaskExecutor m_taskExec;
};

}