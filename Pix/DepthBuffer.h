#pragma once

#include <XEngine.h>

class DepthBuffer
{
public:
	static DepthBuffer* Get();
public:
	void OnNewFrame();
	void Initialize(int width, int height);
	void SetEnabled(bool enabled);
	bool CheckDepthBuffer(int x, int y, float depth);
private:
	std::unique_ptr<float[]> mDepthBuffer;
	int mWidth = 0;
	int mHeight = 0;
	bool mEnabled = false;
};

