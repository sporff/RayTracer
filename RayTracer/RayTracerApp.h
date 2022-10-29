#pragma once
#include "GraphicsWrapper.h"
#include "IRenderer.h"
#include "IObjectManager.h"
#include "ICamera.h"
#include "Sphere.h"
#include "TaskExecutor.h"

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