#pragma once
#include "IObjectManager.h"

namespace RayTracer
{
	class BasicObjectManager : public IObjectManager
	{
	public:
		BasicObjectManager();
		~BasicObjectManager();

		virtual void AddObject(std::shared_ptr<IWorldObject> addObject) override;
		virtual const std::vector<std::shared_ptr<IWorldObject>> GetObjects() override;

	private:
		std::vector<std::shared_ptr<IWorldObject>> m_objectList;
	};

}
