#pragma once
#include "IRenderer.h"

namespace RayTracer
{

class BasicRenderer : public IRenderer
{
public:
	BasicRenderer();
	~BasicRenderer();

	virtual bool Execute(sf::RenderTexture* pTarget, ICamera* pCamera, IObjectManager* pObjectManager, TaskExecutor* pTaskExecutor) override;
private:
	union PixelType
	{
		uint32_t pixel;
		struct { sf::Uint8 r, g, b, a; };
	};

	int m_bufferWidth;
	int m_bufferHeight;
	std::vector<PixelType> m_pixelBuffer;
	std::vector<PixelType> m_backBuffer;
};

}

