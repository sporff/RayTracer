#pragma once
#include "ICamera.h"
#include "TaskExecutor.h"

namespace RayTracer
{

class BasicCamera : public ICamera
{
public:
	BasicCamera();
	virtual ~BasicCamera();

	virtual bool Render(sf::RenderTexture* pTarget, IObjectManager* pObjMgr, TaskExecutor* pTaskExec);

	int GetBufferWidth();

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
