#include "IRenderer.h"

using namespace RayTracer;

IRenderer::IRenderer()
{

}

IRenderer::~IRenderer()
{ }

bool RayTracer::IRenderer::Execute(sf::RenderTexture* pTarget, ICamera* pCamera, IObjectManager* pObjectManager, TaskExecutor* pTaskExecutor)
{
	return false;
}