#include <iostream>
#include "RayTracerApp.h"
#include "BasicCamera.h"
#include "Ray.h"

using namespace RayTracer;

BasicCamera::BasicCamera()
	: m_bufferWidth(300)
	, m_bufferHeight(300)
	, m_pixelBuffer(m_bufferWidth*m_bufferHeight)
	, m_backBuffer(m_bufferWidth* m_bufferHeight)
{
}

BasicCamera::~BasicCamera()
{

}

bool BasicCamera::Render(sf::RenderTexture* pTarget, IObjectManager* pObjMgr, TaskExecutor* pTaskExec)
{
	sf::Vector2u size = pTarget->getSize();

	float FOV = DEGTORAD(90.f);
	float screenDistance = 100.f;
	

	//Vector3f cameraOrigin(-500.f, 0.f, 0.f);
	Vector3f cameraOrigin = m_position;

	Vector3f forwardUnit(0.f, 1.f, 0.f);
	Vector3f upUnit(0.f, 0.f, 1.f);

	// calc screen center
	Vector3f screenCenter = forwardUnit*screenDistance;
	// calc screen width and half width based on FOV and distance
	float screenHalfWidth = screenDistance * std::tan(FOV * 0.5f);
	float screenWidth = screenHalfWidth * 2.f;
	// calc screen height
	float heightToWidthRatio = (float)m_bufferHeight / (float)m_bufferWidth;
	float screenHeight = screenWidth * heightToWidthRatio;
	float screenHalfHeight = screenHeight * 0.5f;
	// calc texel width
	float texelWidth = screenWidth / (float)(m_bufferWidth-1);
	// calc top left of screen
	Vector3f topLeft(								//
		screenCenter.x - screenHalfWidth
		, screenDistance
		, screenCenter.z + screenHalfHeight
	);
	// calc texel spacial vectors
	Vector3f texelRightVec(texelWidth, 0.f, 0.f);	//
	Vector3f texelDownVec(0.f, 0.f, -texelWidth);	//

	//std::cout << "-----------\n";
	Vector3f curLeftSide = topLeft;
	Ray rayToCast(cameraOrigin, cameraOrigin);
	int64_t rowStart = 0;
	auto objs = pObjMgr->GetObjects();

	std::atomic<int> taskRefCount = 0;

	//std::fill(m_pixelBuffer.begin(), m_pixelBuffer.end(), 0);
	std::fill(m_backBuffer.begin(), m_backBuffer.end(), PixelType());

	int rowCountPerThread = 20;
	for (int y = 0; y < m_bufferHeight; y+=rowCountPerThread)
	//for (int y = 0; y < bufferHeight; y++)
	{
		Vector3f curRowPos = curLeftSide;

		int64_t rowColOffset = rowStart;

		taskRefCount++;
		//std::cout << "Task-- : " << taskRefCount << "\n";

		pTaskExec->AddTask(
			[&taskRefCount, y, rowCountPerThread, cameraOrigin, curRowPos, rowColOffset, texelRightVec, texelDownVec, &objs, this]()
			{
				//auto taskStartTime = std::chrono::high_resolution_clock::now();
				Ray rayToCast(cameraOrigin, cameraOrigin);
				Vector3f curRowP = curRowPos;
				int64_t rowColO = rowColOffset;

				for (int rowCount = 0; rowCount < rowCountPerThread; rowCount++)
				{
					for (int x = 0; x < this->GetBufferWidth(); x++)
					{
						rayToCast.SetDirection(curRowP);

						float closestHit = -1.f;
						for (auto& curObj : objs)
						{
							Vector3f intersectPt;
							float t = 0.f;
							if (curObj->GetRayIntersection(rayToCast, &t, &intersectPt))
							{
								float dis = (intersectPt - cameraOrigin).Length();
								if (closestHit < 0.f || dis < closestHit)
								{
									closestHit = dis;
									float maxDis = 30000.f;
									float disScale = 255.f / maxDis;
									/*if (dis > maxDis - 500.f)
										dis = maxDis - 500.f;*/
									float reverseDis = (maxDis - dis);
									uint8_t comp = (int)(reverseDis * disScale);
									m_backBuffer[rowColO].a = 255;
									m_backBuffer[rowColO].r = (int)(comp);
									m_backBuffer[rowColO].g = (int)(comp);
									m_backBuffer[rowColO].b = (int)(comp);
								}
							}
						}

						curRowP += texelRightVec;
						rowColO++;
					}

					curRowP = curRowPos;
					curRowP += texelDownVec * (float)rowCountPerThread;
				}

				/*auto taskEndTime = std::chrono::high_resolution_clock::now();
				std::cout << "  Task time uS: " << std::chrono::duration_cast<std::chrono::nanoseconds>(taskEndTime - taskStartTime).count() << "\n";*/

				taskRefCount--;
				//std::cout << "Task-- : " << taskRefCount << "\n";
			});
		
		//for (int x = 0; x < bufferWidth; x++)
		//{
		//	rayToCast.SetEnd(curRowPos);

		//	for (auto& curObj : pObjMgr->GetObjects())
		//	{
		//		Vector3f intersectPt;
		//		if (curObj->GetRayIntersection(rayToCast, &intersectPt))
		//		{
		//			pixelBuffer[rowColOffset].a = 255;
		//			pixelBuffer[rowColOffset].r = 255;
		//			pixelBuffer[rowColOffset].g = 255;
		//			pixelBuffer[rowColOffset].b = 255;
		//		}
		//	}
		//	/*pixelBuffer[y * bufferWidth + x].a = (int)(x*2.55);
		//	pixelBuffer[y * bufferWidth + x].r = (int)(y*25.5);
		//	pixelBuffer[y * bufferWidth + x].g = 255;
		//	pixelBuffer[y * bufferWidth + x].b = 255;*/
		//	//curRowPos.Print();
		//	curRowPos += texelRightVec;
		//	rowColOffset++;
		//}
		//std::cout << "END ROW: " << y << "\n";
		rowStart += (int64_t)(m_bufferWidth*rowCountPerThread);
		curLeftSide += (texelDownVec*(float)rowCountPerThread);
	}
	//std::cout << "-----------\n";

	while (taskRefCount > 0) { }

	m_pixelBuffer = m_backBuffer;

	sf::Texture tex;
	tex.create((int)m_bufferWidth, (int)m_bufferHeight);
	tex.update((const sf::Uint8*)&(m_pixelBuffer[0]), m_bufferWidth, m_bufferHeight, 0, 0);
	//tex.update(&(pixelTest[0]));// , 100, 100, 0, 0);

	sf::Sprite renderSprite;
	renderSprite.setTexture(tex, true);
	renderSprite.setScale((float)size.x/(float)m_bufferHeight, (float)size.y/(float)m_bufferHeight);
	pTarget->draw(renderSprite);
	
	return true;
}

int BasicCamera::GetBufferWidth()
{
	return m_bufferWidth;
}
