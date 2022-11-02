#include <iostream>

#include "RayTracerConsts.h"
#include "Ray.h"
#include "QuatRotator.h"
#include "RayTracerApp.h"
#include "BasicCamera.h"

using namespace RayTracer;

BasicCamera::BasicCamera()
{
	m_orientation = std::make_shared<QuatRotator>();
}

BasicCamera::~BasicCamera()
{

}
