#pragma once

#include "ICamera.h"

namespace RayTracer
{

class IRenderer
{
public:
	IRenderer();
	virtual ~IRenderer() = 0;

	virtual bool Execute() = 0;
private:

};

}