#include "Graphics.h"

#include "Clipper.h"
#include "DepthBuffer.h"
#include "MatrixStack.h"
#include "PixCamera.h"
#include "Viewport.h"

void Graphics::NewFrame()
{
	MatrixStack::Get()->OnNewFrame();
	DepthBuffer::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	Viewport::Get()->OnNewFrame();
	PixCamera::Get()->OnNewFrame();
}