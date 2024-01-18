#include "DepthBuffer.h"

DepthBuffer* DepthBuffer::Get()
{
	static DepthBuffer sInstance;
	return &sInstance;
}

void DepthBuffer::OnNewFrame()
{
	mEnabled = false;

	const int dimension = mWidth * mHeight;
	for (int i = 0; i < dimension; ++i)
	{
		mDepthBuffer[i] = 1.0f;
	}
}

void DepthBuffer::Initialize(int width, int height)
{
	// If we already have the exact dimension, don't bother
	if (width != mWidth || height != mHeight)
	{
		mDepthBuffer = std::make_unique<float[]>(width * height);
		mWidth = width;
		mHeight = height;
	}
}

void DepthBuffer::SetEnabled(bool enabled)
{
	mEnabled = enabled;
}

bool DepthBuffer::CheckDepthBuffer(int x, int y, float depth)
{
	// Not using depth buffer, always pass
	if (!mEnabled)
		return true;

	// Pixel out of bound, always fail
	if ((x < 0 && x > mWidth) && (y < 0 && y > mHeight))
		return false;

	// Pixel too far, fail
	const int index = x + (y * mWidth);
	if (depth > mDepthBuffer[index])
		return false;
	
	// Record new depth, pass
	mDepthBuffer[index] = depth;
	return true;
}