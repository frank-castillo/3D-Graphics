#include "PixCamera.h"
#include <XEngine.h>

using namespace X;

PixCamera* PixCamera::Get()
{
	static PixCamera sInstance;
	return &sInstance;
}

PixCamera::PixCamera()
	: mPosition(Vector3::Zero()),
	mDirection(Vector3::ZAxis()),
	mNearPlane(0.01f),
	mFarPlane(100.0f),
	mFOV (1.57f)
{

}

void PixCamera::OnNewFrame()
{
	*this = {};
}

void PixCamera::SetPosition(Vector3 position)
{
	mPosition = position;
}

void PixCamera::SetDirection(Vector3 direction)
{
	mDirection = Normalize(direction);
	// Normalize so we only get the direction and not in the vector itself
}

void PixCamera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void PixCamera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void PixCamera::SetFOV(float fov)
{
	mFOV = fov;
}

Matrix4 PixCamera::GetViewMatrix() const
{
	const Vector3 l = mDirection;
	const Vector3 r = Normalize(Cross(Vector3::YAxis(), mDirection)); // Get Middle finger when using left hand system
	const Vector3 u = Normalize(Cross(l, r)); // Find the up vector -> 
	float x = -Dot(r, mPosition);
	float y = -Dot(u, mPosition);
	float z = -Dot(l, mPosition);

	return Matrix4
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}

Matrix4 PixCamera::GetProjectionMatrix() const
{
	//extern int screenWidth;
	//extern int screenHeight;

	extern float gResolutionX;
	extern float gResolutionY;

	const float aspect = gResolutionX / gResolutionY;
	const float h = 1 / tan(mFOV * 0.5f);
	const float w = h / aspect;
	const float f = mFarPlane;
	const float n = mNearPlane;
	const float d = f / (f - n);

	return Matrix4
	(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, h, 0.0f, 0.0f,
		0.0f, 0.0f, d, 1.0f,
		0.0f, 0.0f, -n * d, 0.0f
	);
}