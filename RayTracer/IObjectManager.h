#pragma once

#include <vector>
#include <memory>

#include "IWorldObject.h"

namespace RayTracer
{

class IObjectManager
{
public:
	IObjectManager();
	~IObjectManager();

	virtual void AddObject(std::shared_ptr<IWorldObject> addObject) = 0;
	virtual const std::vector<std::shared_ptr<IWorldObject>> GetObjects() = 0;

private:
	
};

}
 