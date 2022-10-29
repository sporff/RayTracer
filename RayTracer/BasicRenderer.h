#pragma once
#include "IRenderer.h"

namespace RayTracer
{

class BasicRenderer : public IRenderer
{
public:
	BasicRenderer();
	~BasicRenderer();

	virtual bool Execute() override;
private:
};

}

