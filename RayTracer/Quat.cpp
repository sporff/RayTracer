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

RayTracer::Quat::Quat(const Vector3f& v)
{
	Set(v);
}

void Quat::Set(const Quat& q)
{
	this->X = q.X;
	this->Y = q.Y;
	this->Z = q.Z;
	this->W = q.W;
}

/*
* 
*/
void RayTracer::Quat::Set(float xAngle, float yAngle, float zAngle)
{
	float angle;

	angle = yAngle * 0.5f;
	float rollSin = sin(angle);
	float rollCos = cos(angle);

	angle = xAngle * 0.5f;
	float pitchSin = sin(angle);
	float pitchCos = cos(angle);

	angle = zAngle * 0.5f;
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

void Quat::Set(float X, float Y, float Z, float W)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
	this->W = W;
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

Vector3f Quat::ToEuler()
{
	//Vector3f euler;

	//const float sqw = W*W;
	//const float sqx = X*X;
	//const float sqy = Y*Y;
	//const float sqz = Z*Z;
	//const float test = 2.0 * (Y*W - X*Z);

	//auto equals = [](float test, float value, float epsilon) -> bool
	//{
	//	return false;
	//};

	//auto clamp = [](float test, float min, float max) -> float
	//{
	//	if (test < min) return min;
	//	if (test > max) return max;
	//	return test;
	//};

	//if (equals(test, 1.0, 0.000001))
	//{
	//	// heading = rotation about z-axis
	//	euler.z = (float) (-2.0*atan2(X, W));
	//	// bank = rotation about x-axis
	//	euler.x = 0;
	//	// attitude = rotation about y-axis
	//	euler.y = (float) (3.14159f/2.0);
	//}
	//else if (equals(test, -1.0, 0.000001))
	//{
	//	// heading = rotation about z-axis
	//	euler.z = (float) (2.0*atan2(X, W));
	//	// bank = rotation about x-axis
	//	euler.x = 0;
	//	// attitude = rotation about y-axis
	//	euler.y = (float) (3.14159f/-2.0);
	//}
	//else
	//{
	//	// heading = rotation about z-axis
	//	euler.z = (float) atan2(2.0 * (X*Y +Z*W),(sqx - sqy - sqz + sqw));
	//	// bank = rotation about x-axis
	//	euler.x = (float) atan2(2.0 * (Y*Z +X*W),(-sqx - sqy + sqz + sqw));
	//	// attitude = rotation about y-axis
	//	euler.y = (float) asin( clamp(test, -1.0, 1.0) );
	//}
	//return euler;

	float t0 = 2.f * (W * X + Y * Z);
	float t1 = 1.f - 2.f * (X * X + Y * Y);
	float roll_x = atan2(t0, t1);

	float t2 = 2.f * (W * Y - Z * X);
	t2 = (t2 > 1.f) ? 1.f : t2;
	t2 = (t2 < -1.f) ? -1.f : t2;
	float pitch_y = asin(t2);

	float t3 = 2.f * (W * Z + X * Y);
	float t4 = 1.f - 2.f * (Y * Y + Z * Z);
	float yaw_z = atan2(t3, t4);

	return Vector3f(yaw_z, pitch_y, roll_x);
}

Quat Quat::Inverse() const
{
	return Quat(-X, -Y, -Z, W);
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
		(B.W * W) - (B.X * X) - (B.Y * Y) - (B.Z * Z)
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
	//return Multiply(v);
	//auto iq = this->Inverse();
	//Quat qv(v);
	Quat qv(v.x, v.y, v.z, 0.f);
	Quat result(*this * qv * this->Inverse());
	return Vector3f(result.X, result.Y, result.Z);

	//return Vector3f(this->X, this->Y, this->Z);
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


