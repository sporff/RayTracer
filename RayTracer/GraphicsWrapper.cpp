#include "GraphicsWrapper.h"

using namespace RayTracer;

GraphicsWrapper::GraphicsWrapper(std::string windowTitle, int windowWidth, int windowHeight)
	: m_pWindow(nullptr)
	, m_pBackBuff(nullptr)
{
	m_pWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle);
	if (m_pWindow != nullptr)
	{
		m_pBackBuff = new sf::RenderTexture();
		if (m_pBackBuff != nullptr)
		{
			m_pBackBuff->create(windowWidth, windowHeight);
		}
	}
}

GraphicsWrapper::~GraphicsWrapper()
{
	if (m_pWindow != nullptr)
	{
		delete m_pWindow;
		m_pWindow = nullptr;
	}
}

bool GraphicsWrapper::IsWindowOpen()
{
	return false;
}

sf::RenderWindow* GraphicsWrapper::GetWindow()
{
	return m_pWindow;
}

sf::RenderTexture* GraphicsWrapper::GetRenderTexture()
{
	return m_pBackBuff;
}
