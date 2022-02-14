#pragma once

#include <SFML/Graphics.hpp>
#include "Vector3f.h"
#include "TaskExecutor.h"

namespace RayTracer
{

	class IObjectManager;

	class ICamera
	{
	public:
		ICamera();
		virtual ~ICamera() = 0;

		void SetPosition(const Vector3f& pos);
		void AddToPosition(const Vector3f& v);
		Vector3f GetPosition();

		virtual bool Render(sf::RenderTexture* pTarget, IObjectManager* pObjMgr, TaskExecutor* pTaskExec) = 0;

	protected:
		Vector3f m_position;
	};

}