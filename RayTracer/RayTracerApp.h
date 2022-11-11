#pragma once
#include <set>
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

	void KeyDownEvent(sf::Keyboard::Key key);
	void KeyUpEvent(sf::Keyboard::Key key);
	bool IsKeyPressed(sf::Keyboard::Key key);

private:
	GraphicsWrapper m_graphicsWrapper;
	IRenderer* m_pRenderer;
	IObjectManager* m_pObjectManager;
	ICamera* m_pCamera;

	TaskExecutor m_taskExec;

	std::set<sf::Keyboard::Key> m_keys;
};

}