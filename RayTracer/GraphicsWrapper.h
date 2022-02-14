#pragma once
#include <SFML/Graphics.hpp>

namespace RayTracer
{

class GraphicsWrapper
{
public:
	GraphicsWrapper(std::string windowTitle, int windowWidth, int windowHeight);
	~GraphicsWrapper();

	bool IsWindowOpen();

	sf::RenderWindow* GetWindow();
	sf::RenderTexture* GetRenderTexture();

private:
	sf::RenderWindow* m_pWindow;
	sf::RenderTexture* m_pBackBuff;
};

}