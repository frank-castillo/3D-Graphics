#include "Rasterizer.h"
#include "DepthBuffer.h"

namespace
{
	// Global scope (::), do not clutter it more
	// Nameless namespace are only visible to the .cpp they are in
	bool IsFlatBottom(Vertex v1, Vertex v2, Vertex v3, Vertex& top, Vertex& bottomRight, Vertex& bottomLeft)
	{
		if (v1.pos.y == v2.pos.y && v3.pos.y < v1.pos.y)
		{
			top = v3;
			if (v1.pos.x > v2.pos.x)
			{
				bottomRight = v1;
				bottomLeft = v2;
			}
			else
			{
				bottomRight = v2;
				bottomLeft = v1;
			}
			return true;
		}

		else if (v2.pos.y == v3.pos.y && v1.pos.y < v2.pos.y)
		{
			top = v1;
			if (v2.pos.x > v3.pos.x)
			{
				bottomRight = v2;
				bottomLeft = v3;
			}
			else
			{
				bottomRight = v3;
				bottomLeft = v2;
			}
			return true;
		}

		else if (v3.pos.y == v1.pos.y && v2.pos.y < v3.pos.y)
		{
			top = v2;
			if (v3.pos.x > v1.pos.x)
			{
				bottomRight = v3;
				bottomLeft = v1;
			}
			else
			{
				bottomRight = v1;
				bottomLeft = v3;
			}
			return true;
		}
		return false;
	}

	bool IsFlatTop(Vertex v1, Vertex v2, Vertex v3, Vertex& topLeft, Vertex& topRight, Vertex& bottom)
	{
		if (v1.pos.y == v2.pos.y && v3.pos.y > v1.pos.y)
		{
			bottom = v3;
			if (v1.pos.x > v2.pos.x)
			{
				topRight = v1;
				topLeft = v2;
			}
			else
			{
				topRight = v2;
				topLeft = v1;
			}
			return true;
		}

		else if (v2.pos.y == v3.pos.y && v1.pos.y > v2.pos.y)
		{
			bottom = v1;
			if (v2.pos.x > v3.pos.x)
			{
				topRight = v2;
				topLeft = v3;
			}
			else
			{
				topRight = v3;
				topLeft = v2;
			}
			return true;
		}

		else if (v3.pos.y == v1.pos.y && v2.pos.y > v3.pos.y)
		{
			bottom = v2;
			if (v3.pos.x > v1.pos.x)
			{
				topRight = v3;
				topLeft = v1;
			}
			else
			{
				topRight = v1;
				topLeft = v3;
			}
			return true;
		}
		return false;
	}

	void FindSplitVertex(Vertex v1, Vertex v2, Vertex v3, Vertex& splitVertex, Vertex& topVertex, Vertex& midVertex, Vertex& bottomVertex)
	{
		if (v1.pos.y > v2.pos.y && v2.pos.y > v3.pos.y)
		{
			topVertex = v1;
			midVertex = v2;
			bottomVertex = v3;
		}
		else if (v1.pos.y > v3.pos.y && v3.pos.y > v2.pos.y)
		{
			topVertex = v1;
			midVertex = v3;
			bottomVertex = v2;
		}
		else if (v2.pos.y > v3.pos.y && v3.pos.y > v1.pos.y)
		{
			topVertex = v2;
			midVertex = v3;
			bottomVertex = v1;
		}
		else if (v2.pos.y > v1.pos.y && v1.pos.y > v3.pos.y)
		{
			topVertex = v2;
			midVertex = v1;
			bottomVertex = v3;
		}
		else if (v3.pos.y > v1.pos.y && v1.pos.y > v2.pos.y)
		{
			topVertex = v3;
			midVertex = v1;
			bottomVertex = v2;
		}
		else if (v3.pos.y > v2.pos.y && v2.pos.y > v1.pos.y)
		{
			topVertex = v3;
			midVertex = v2;
			bottomVertex = v1;
		}

		float t = (midVertex.pos.y - topVertex.pos.y) / (bottomVertex.pos.y - topVertex.pos.y);
		splitVertex = LerpVertex(topVertex, bottomVertex, t);
		splitVertex.pos.y = midVertex.pos.y;
	}
}

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(Vertex v)
{
	const int x = static_cast<int>(v.pos.x + 0.5f);
	const int y = static_cast<int>(v.pos.y + 0.5f);

	if (DepthBuffer::Get()->CheckDepthBuffer(x, y, v.pos.z))
	{
		X::DrawPixel(x, y, v.color);
	}
}

void Rasterizer::DrawLine(Vertex v1, Vertex v2)
{
	float dx = v2.pos.x - v1.pos.x;
	float dy = v2.pos.y - v1.pos.y;;
	float m = dy / dx;
	float b = v1.pos.y - (m * v1.pos.x);
	float absM = abs(m);

	if (v1.pos == v2.pos)
	{
		DrawPoint(v1);
		return;
	}

	if (absM < 1) // X traversal
	{
		float startX = v1.pos.x;
		float endX = v2.pos.x;

		if (dx < 0)
		{
			std::swap(startX, endX);
		}

		for (float i = startX; i <= endX; i += 1.0f)
		{
			const float t = (i - startX) / (endX - startX);
			Vertex v = LerpVertex(v1, v2, t);
			DrawPoint(v);
		}
	}
	else if (absM >= 1) // Y traversal
	{
		float startY = v1.pos.y;
		float endY = v2.pos.y;

		if (dy < 0)
		{
			std::swap(startY, endY);
		}

		for (float i = startY; i <= endY; i += 1.0f)
		{
			const float t = (i - startY) / (endY - startY);
			Vertex v = LerpVertex(v1, v2, t);
			DrawPoint(v);
		}
	}
}

void Rasterizer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	if (mFillMode == FillMode::Wireframe)
	{
		DrawTriangleWireframe(v1, v2, v3);
	}
	else if (mFillMode == FillMode::Solid)
	{
		DrawTriangleFilled(v1, v2, v3);
	}
	else
	{
		return;
	}
}

void Rasterizer::DrawTriangleWireframe(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	DrawLine(v1, v2);
	DrawLine(v2, v3);
	DrawLine(v3, v1);
}

void Rasterizer::DrawTriangleFilled(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	// Flat Bottom
	Vertex top;
	Vertex bottomRight;
	Vertex bottomLeft;

	// Flat top
	Vertex bottom;
	Vertex topLeft;
	Vertex topRight;

	// Neither
	Vertex splitVertex;
	Vertex midVertex;

	if (IsFlatBottom(v1, v2, v3, top, bottomRight, bottomLeft))
	{
		for (float y = top.pos.y; y <= bottomRight.pos.y; y += 1.0f)
		{
			float t = (y - top.pos.y) / (bottomRight.pos.y - top.pos.y); // This is our whole journey
			Vertex left = LerpVertex(top, bottomLeft, t);
			Vertex right = LerpVertex(top, bottomRight, t);
			DrawLine(left, right);
		}
	}
	else if (IsFlatTop(v1, v2, v3, topLeft, topRight, bottom))
	{
		for (float y = topLeft.pos.y; y <= bottom.pos.y; y += 1.0f)
		{
			float t = (y - topLeft.pos.y) / (bottom.pos.y - topRight.pos.y); // This is our whole journey
			Vertex left = LerpVertex(bottom, topLeft, t);
			Vertex right = LerpVertex(bottom, topRight, t);
			DrawLine(left, right);
		}
	}
	else
	{
		FindSplitVertex(v1, v2, v3, splitVertex, top, midVertex, bottom);
		DrawTriangleFilled(top, splitVertex, midVertex);
		DrawTriangleFilled(midVertex, splitVertex, bottom);
	}

	DrawTriangleWireframe(v1, v2, v3);
}