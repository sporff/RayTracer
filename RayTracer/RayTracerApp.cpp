#include <iostream>
#include <chrono>
#include "RayTracerApp.h"
#include "BasicCamera.h"
#include "BasicObjectManager.h"
#include "Sphere.h"

using namespace RayTracer;

RayTracerApp::RayTracerApp()
	: m_graphicsWrapper("Ray Tracer", 1600, 1600)
	, m_camera(nullptr)
	, m_taskExec(8)
{
	m_camera = new BasicCamera();
	m_camera->SetPosition(Vector3f(0.f, -10000.f, 0.f));

	m_pObjectManager = new BasicObjectManager();

	m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(1000.f, 10000.f, -1000.f), 1000.f));
	m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(0.f, 1000.f, 0.f), 200.f));
	m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(-1000.f, 20000.f, -5000.f), 5000.f));

	for (int i = 0; i < 10; i++)
	{
		float x = (float)((rand() % 10000) / 2) - 2000.f;
		float y = (float)((rand() % 20000)) + 500.f;
		float z = (float)((rand() % 10000) / 2) - 2000.f;
		float r = (float)((rand() % 1000));
		m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(x,y,z), r));
	}
}

RayTracerApp::~RayTracerApp()
{
	if (m_camera != nullptr)
		delete m_camera;

	if (m_pObjectManager != nullptr)
		delete m_pObjectManager;
}

bool RayTracerApp::Execute()
{
	auto pWindow = m_graphicsWrapper.GetWindow();
	auto pRenderTexture = m_graphicsWrapper.GetRenderTexture();
	auto prevFrameEnd = std::chrono::high_resolution_clock::now();

	auto lastPrint = std::chrono::high_resolution_clock::now();


	while (pWindow->isOpen())
	{
		sf::Event event;
		while (pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				pWindow->close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					m_camera->AddToPosition(Vector3f(0.f, 100.f, 0.f));
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					m_camera->AddToPosition(Vector3f(0.f, -100.f, 0.f));
				}

				if (event.key.code == sf::Keyboard::Right)
				{
					m_camera->AddToPosition(Vector3f(100.f, 0.f, 0.f));
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					m_camera->AddToPosition(Vector3f(-100.f, 0.f, 0.f));
				}

				if (event.key.code == sf::Keyboard::R)
				{
					m_camera->AddToPosition(Vector3f(0.f, 0.f, 100.f));
				}
				if (event.key.code == sf::Keyboard::F)
				{
					m_camera->AddToPosition(Vector3f(0.f, 0.f, -100.f));
				}
			}
		}

		if (m_camera != nullptr)
		{
			sf::Vector2i position = sf::Mouse::getPosition(*pWindow);
			sf::Vector2u winSize = pWindow->getSize();

			sf::Vector2f mouseCenterOffset(
				((float)position.x - (float)winSize.x / 2.f) * 0.5f,
				((float)position.y - (float)winSize.y / 2.f) * 2.0f
			);
			/*std::cout << position.x << ", " << position.y << "\n";
			std::cout << winSize.x << ", " << winSize.y << "\n";
			std::cout << mouseCenterOffset.x << ", " << mouseCenterOffset.y << "\n";
			std::cout << "--------\n";*/

			//m_camera->SetPosition(Vector3f(mouseCenterOffset.x, 0.f, mouseCenterOffset.y));
			//m_camera->SetPosition(Vector3f(mouseCenterOffset.x, mouseCenterOffset.y, 0.f));

			m_camera->Render(pRenderTexture, m_pObjectManager, &m_taskExec);
		}

		pRenderTexture->display();
		sf::Sprite renderTextureSprite(pRenderTexture->getTexture());
		pWindow->draw(renderTextureSprite);
		pWindow->display();
		pRenderTexture->clear();

		auto newFrameEnd = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(newFrameEnd - lastPrint).count() > 1000)
		{
			std::cout << "Frame time uS: " << std::chrono::duration_cast<std::chrono::nanoseconds>(newFrameEnd - prevFrameEnd).count() << "\n";

			auto camPos = m_camera->GetPosition();
			std::cout << "Camera: " << camPos.x << ", " << camPos.y << ", " << camPos.z << "\n";
			lastPrint = newFrameEnd;
		}
		prevFrameEnd = newFrameEnd;
	}

	return true;
}
