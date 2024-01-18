#pragma once
#include <XEngine.h>

#include "Vertex.h"

enum class FillMode
{
	None,
	Solid,
	Wireframe
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);

	void DrawPoint(int x, int y);
	void DrawPoint(Vertex v);
	void DrawLine(Vertex v1, Vertex v2);
	void DrawTriangle(Vertex v1, Vertex v2, Vertex v3);

private:
	void DrawTriangleWireframe(const Vertex& v1, const Vertex& v2, const Vertex& v3);
	void DrawTriangleFilled(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
};