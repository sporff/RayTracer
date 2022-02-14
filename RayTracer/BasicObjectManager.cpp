#include "BasicObjectManager.h"

using namespace RayTracer;

BasicObjectManager::BasicObjectManager()
{

}

BasicObjectManager::~BasicObjectManager()
{

}

void BasicObjectManager::AddObject(std::shared_ptr<IWorldObject> addObject)
{
	m_objectList.push_back(addObject);
}

const std::vector<std::shared_ptr<RayTracer::IWorldObject>> BasicObjectManager::GetObjects()
{
	return m_objectList;
}
