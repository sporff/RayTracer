#include <cmath>
#include "Quat.h"

using namespace RayTracer;

Quat::Quat()
{
	Set(0.f, 0.f, 0.f, 1.f);
}

Quat::Quat(float X, float Y, float Z, float W)
{
	Set(X, Y, Z, W);
}

void Quat::Set(const Quat& q)
{
	this->X = q.X;
	this->Y = q.Y;
	this->Z = q.Z;
	this->W = q.W;
}

void Quat::Set(float X, float Y, float Z, float W)
{
	Set(Quat(X, Y, Z, W));
}

void Quat::Set(const Vector3f& vec)
{
	float angle;

	angle = vec.x * 0.5f;
	float rollSin = sin(angle);
	float rollCos = cos(angle);

	angle = vec.x * 0.5f;
	float pitchSin = sin(angle);
	float pitchCos = cos(angle);

	angle = vec.x * 0.5f;
	float yawSin = sin(angle);
	float yawCos = cos(angle);

	float pitchCos_yawCos = pitchCos * yawCos;
	float pitchSin_yawCos = pitchSin * yawCos;
	float pitchCos_yawSin = pitchCos * yawSin;
	float pitchSin_yawSin = pitchSin * yawSin;

	X = rollSin * pitchCos_yawCos - rollCos * pitchSin_yawSin;
	Y = rollCos * pitchSin_yawCos + rollSin * pitchCos_yawSin;
	Z = rollCos * pitchCos_yawSin - rollSin * pitchSin_yawCos;
	W = rollCos * pitchCos_yawCos + rollSin * pitchSin_yawSin;
}

/**
 * Returns if 2 quaternions are equal
 * TODO This should probably not use == on floats
 */
bool Quat::Equals(const Quat& B) const
{
	return (X == B.X && Y == B.Y && Z == B.Z && W == B.W);
}

Quat Quat::Multiply(const Quat& B) const
{
	return Quat
	(
		(B.W * X) + (B.X * W) + (B.Y * Z) - (B.Z * Y),
		(B.W * Y) + (B.Y * W) + (B.Z * X) - (B.X * Z),
		(B.W * Z) + (B.Z * W) + (B.X * Y) - (B.Y * X),
		(B.W * W) + (B.X * X) + (B.Y * Y) + (B.Z * Z)
	);
}

Vector3f Quat::Multiply(const Vector3f& v) const
{
	Vector3f uv, uuv;
	Vector3f qvec(X, Y, Z);
	uv = qvec.Cross(v);
	uuv = qvec.Cross(uv);
	uv *= (2.0f * W);

	return v + uv + uuv;
};

Quat Quat::operator*(const Quat& B) const
{
	return Multiply(B);
}

Quat Quat::operator*=(const Quat& B)
{
	Set(Multiply(B));

	return *this;
}

Vector3f Quat::operator*(const Vector3f& v) const
{
	return Multiply(v);
}

Quat& Quat::operator=(const Quat& from)
{
	X = from.X;
	Y = from.Y;
	Z = from.Z;
	W = from.W;

	return *this;
};

bool Quat::operator==(const Quat& B) const
{
	return Equals(B);
}


