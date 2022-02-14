#include "IObjectManager.h"

using namespace RayTracer;

IObjectManager::IObjectManager()
{

}

IObjectManager::~IObjectManager()
{

}

void IObjectManager::AddObject(std::shared_ptr<IWorldObject> addObject)
{
	
}

const std::vector<std::shared_ptr<RayTracer::IWorldObject>> IObjectManager::GetObjects()
{
	return {};
}
