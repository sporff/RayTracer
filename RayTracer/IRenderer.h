#pragma once

#include "ICamera.h"

namespace RayTracer
{

class IRenderer
{
public:
	IRenderer();
	virtual ~IRenderer() = 0;

	virtual bool Execute(sf::RenderTexture* pTarget, ICamera* pCamera, IObjectManager* pObjectManager, TaskExecutor* pTaskExecutor) = 0;
private:

};

}