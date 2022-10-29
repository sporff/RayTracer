#include "ICamera.h"
#include "IObjectManager.h"

using namespace RayTracer;

ICamera::ICamera()
{ }

ICamera::~ICamera()
{ }

void ICamera::SetPosition(const Vector3f& pos)
{
	m_position = pos;
}

Vector3f ICamera::GetPosition()
{
	return m_position;
}

void ICamera::AddToPosition(const Vector3f& v)
{
	m_position += v;
}
