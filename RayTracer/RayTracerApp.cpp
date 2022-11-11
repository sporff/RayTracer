#include <iostream>
#include <chrono>
#include "RayTracerConsts.h"
#include "RayTracerApp.h"
#include "BasicRenderer.h"
#include "BasicCamera.h"
#include "BasicObjectManager.h"
#include "Sphere.h"
#include "Cuboid.h"

using namespace RayTracer;

RayTracerApp::RayTracerApp()
	: m_graphicsWrapper("Ray Tracer", 1600, 1600)
	, m_pRenderer(nullptr)
	, m_pCamera(nullptr)
	, m_taskExec(8)
{
	// Temporarily create basic versions of things here
	// In the future, pass it in to constructor?

	m_pRenderer = new BasicRenderer();
	
	m_pCamera = new BasicCamera();
	//m_pCamera->SetPosition(Vector3f(-10000.f, -10000.f, 0.f));
	m_pCamera->SetPosition(Vector3f(0.f, 0.f, 0.f));
	
	m_pObjectManager = new BasicObjectManager();

	//m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(1000.f, 10000.f, -1000.f), 1000.f));
	m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(0.f, 1000.f, 0.f), 200.f));
	//m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(-1000.f, 20000.f, -5000.f), 5000.f));

	m_pObjectManager->AddObject(std::make_shared<Cuboid>(Vector3f(1000.f, 2000.f, -300.f), Vector3f(200.f, 200.f, 200.f)));

	/*for (int i = 0; i < 2; i++)
	{
		float x = (float)((rand() % 10000) / 2) - 2000.f;
		float y = (float)((rand() % 20000)) + 500.f;
		float z = (float)((rand() % 10000) / 2) - 2000.f;
		float r = (float)((rand() % 1000));
		m_pObjectManager->AddObject(std::make_shared<Sphere>(Vector3f(x,y,z), r));
	}*/
}

RayTracerApp::~RayTracerApp()
{
	if (m_pRenderer != nullptr)
		delete m_pRenderer;

	if (m_pCamera != nullptr)
		delete m_pCamera;

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
		/*SFML events*/
		sf::Event event;
		while (pWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				pWindow->close();
			else if (event.type == sf::Event::KeyPressed)
			{
				KeyDownEvent(event.key.code);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				KeyUpEvent(event.key.code);
			}
		}

		float moveAmt = 10.f;
		if (IsKeyPressed(sf::Keyboard::W))
		{
			m_pCamera->AddToPosition(Vector3f(0.f, moveAmt, 0.f));
		}
		if (IsKeyPressed(sf::Keyboard::S))
		{
			m_pCamera->AddToPosition(Vector3f(0.f, -moveAmt, 0.f));
		}

		if (IsKeyPressed(sf::Keyboard::D))
		{
			m_pCamera->AddToPosition(Vector3f(moveAmt, 0.f, 0.f));
		}
		if (IsKeyPressed(sf::Keyboard::A))
		{
			m_pCamera->AddToPosition(Vector3f(-moveAmt, 0.f, 0.f));
		}

		if (IsKeyPressed(sf::Keyboard::R))
		{
			m_pCamera->AddToPosition(Vector3f(0.f, 0.f, moveAmt));
		}
		if (IsKeyPressed(sf::Keyboard::F))
		{
			m_pCamera->AddToPosition(Vector3f(0.f, 0.f, -moveAmt));
		}

		float rotDegrees = 5.f;
		if (IsKeyPressed(sf::Keyboard::Q))
		{
			QuatRotator qr;
			qr.Set(0.f, 0.f, DEGTORAD(rotDegrees));
			m_pCamera->AddToOrientation(qr);
		}
		if (IsKeyPressed(sf::Keyboard::E))
		{
			QuatRotator qr;
			qr.Set(0.f, 0.f, DEGTORAD(-rotDegrees));
			m_pCamera->AddToOrientation(qr);
		}

		/*Render Scene*/
		//if (m_pCamera != nullptr)
		//{
		//	sf::Vector2i position = sf::Mouse::getPosition(*pWindow);
		//	sf::Vector2u winSize = pWindow->getSize();

		//	sf::Vector2f mouseCenterOffset(
		//		((float)position.x - (float)winSize.x / 2.f) * 0.5f,
		//		((float)position.y - (float)winSize.y / 2.f) * 2.0f
		//	);
		//	/*std::cout << position.x << ", " << position.y << "\n";
		//	std::cout << winSize.x << ", " << winSize.y << "\n";
		//	std::cout << mouseCenterOffset.x << ", " << mouseCenterOffset.y << "\n";
		//	std::cout << "--------\n";*/

		//	//m_camera->SetPosition(Vector3f(mouseCenterOffset.x, 0.f, mouseCenterOffset.y));
		//	//m_camera->SetPosition(Vector3f(mouseCenterOffset.x, mouseCenterOffset.y, 0.f));

		//	m_pCamera->Render(pRenderTexture, m_pObjectManager, &m_taskExec);
		//}

		if (m_pRenderer != nullptr)
		{
			m_pRenderer->Execute(pRenderTexture, m_pCamera, m_pObjectManager, &m_taskExec);
		}

		/*SFML update display*/
		pRenderTexture->display();
		sf::Sprite renderTextureSprite(pRenderTexture->getTexture());
		pWindow->draw(renderTextureSprite);
		pWindow->display();
		pRenderTexture->clear();

		/*Temporary*/
		auto newFrameEnd = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(newFrameEnd - lastPrint).count() > 1000)
		{
			//std::cout << "Frame time uS: " << std::chrono::duration_cast<std::chrono::nanoseconds>(newFrameEnd - prevFrameEnd).count() << "\n";

			auto camPos = m_pCamera->GetPosition();
			//std::cout << "Camera: " << camPos.x << ", " << camPos.y << ", " << camPos.z << "\n";
			lastPrint = newFrameEnd;
		}
		prevFrameEnd = newFrameEnd;
	}

	return true;
}

void RayTracerApp::KeyDownEvent(sf::Keyboard::Key key)
{
	m_keys.insert(key);
}

void RayTracerApp::KeyUpEvent(sf::Keyboard::Key key)
{
	m_keys.erase(key);
}

bool RayTracerApp::IsKeyPressed(sf::Keyboard::Key key)
{
	return m_keys.find(key) != m_keys.end();
}
