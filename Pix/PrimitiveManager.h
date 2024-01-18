#pragma once
#include "Vertex.h"

// Responsible for collecting vertex data and feeding primitives one at a time to the Rasterizer

enum class Topology
{
	None,
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None,
	Front,
	Back
};

class PrimitiveManager
{
public:
	static class PrimitiveManager* Get();

public:
	bool BeginDraw(Topology topology, bool applyTransform);
	void AddVertex(Vertex vertex);
	bool EndDraw();

	void SetCullMode(CullMode mode);

private:
	std::vector<Vertex> mVertexBuffer; // Container for our vertices
	Topology mTopology = Topology::Triangle; // Type of shape we want to rasterizer
	CullMode mCullMode = CullMode::Back;
	bool mDrawBegin = false; // Are we drawing?
	bool mApplyTransform = false;
};

