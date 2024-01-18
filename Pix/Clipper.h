#pragma once

#include "Vertex.h"

class Clipper
{
public:
	static Clipper* Get();
public:
	void OnNewFrame();		// Call this in Graphics::NewFrame()

	// Return true if clip test pass
	bool ClipPoint(Vertex v);
	bool ClipLine(Vertex& v1, Vertex& v2);
	bool ClipTriangle(std::vector<Vertex>& vertices);
	bool IsClipping() const { return mClipping; }
	void SetClipping(bool clip) { mClipping = clip; }

private:
	bool mClipping = false;
};