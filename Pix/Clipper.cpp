#include "Clipper.h"

#include "Viewport.h"

namespace
{
	typedef int OutCode;

	const int INSIDE = 0x0000; // 0000
	const int LEFT   = 0x0001; // 0001
	const int RIGHT  = 0x0010; // 0010
	const int BOTTOM = 0x0100; // 0100
	const int TOP    = 0x1000; // 1000

	// Compute the bit code for a point (x, y) using the clip
	// bounded diagonally by (xmin, ymin), and (xmax, ymax)

	// ASSUME THAT xmax, xmin, ymax and ymin are global constants.

	OutCode ComputeOutCode(float x, float y)
	{
		OutCode code;

		code = INSIDE;          // initialised as being inside of [[clip window]]

		if (x < Viewport::Get()->GetMinX())           // to the left of clip window
			code |= LEFT;
		else if (x > Viewport::Get()->GetMaxX())      // to the right of clip window
			code |= RIGHT;
		if (y < Viewport::Get()->GetMinY())           // below the clip window
			code |= BOTTOM;
		else if (y > Viewport::Get()->GetMaxY())      // above the clip window
			code |= TOP;

		return code;
	}

	// Cohen–Sutherland clipping algorithm clips a line from
	// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
	// diagonal from (xmin, ymin) to (xmax, ymax).
}

Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

void Clipper::OnNewFrame()
{
	*this = {};
}

bool Clipper::ClipPoint(Vertex v)
{
	if (!mClipping)
		return true;

	Viewport* viewport = Viewport::Get();

	// Do clipping
	float maxX = viewport->GetMaxX();
	float minX = viewport->GetMinX();
	float maxY = viewport->GetMaxY();
	float minY = viewport->GetMinY();

	if ((v.pos.x > minX && v.pos.x < maxX) &&
		(v.pos.y > minY && v.pos.y < maxY))
		return true;
	else
		return false;
}

bool Clipper::ClipLine(Vertex& v1, Vertex& v2)
{
	if (!mClipping)
		return true;

	// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
	OutCode outcode0 = ComputeOutCode(v1.pos.x, v1.pos.y);
	OutCode outcode1 = ComputeOutCode(v2.pos.x, v2.pos.y);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1))
		{
			// bitwise OR is 0: both points inside window; trivially accept and exit loop
			accept = true;
			break;
		}
		else if (outcode0 & outcode1)
		{
			// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		}
		else
		{
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			float t;
			Viewport* viewport = Viewport::Get();

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			// Now find the intersection point;
			// use formulas:
			//   slope = (y1 - y0) / (x1 - x0)
			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
			// No need to worry about divide-by-zero because, in each case, the
			// outcode bit being tested guarantees the denominator is non-zero
			// 
			// We do not use X and Y calculations as our vertex also has Color information, so we calculate the rate of change (t)
			// and use that value to obtain a lerped vertex with changes in color and position
			if (outcodeOut & TOP)
			{           // point is above the clip window
				t = (viewport->GetMaxY() - v1.pos.y) / (v2.pos.y - v1.pos.y);
			}
			else if (outcodeOut & BOTTOM)
			{ // point is below the clip window
				t = (viewport->GetMinY() - v1.pos.y) / (v2.pos.y - v1.pos.y);
			}
			else if (outcodeOut & RIGHT)
			{  // point is to the right of clip window
				t = (viewport->GetMaxX() - v1.pos.x) / (v2.pos.x - v1.pos.x);
			}
			else if (outcodeOut & LEFT)
			{   // point is to the left of clip window
				t = (viewport->GetMinX() - v1.pos.x) / (v2.pos.x - v1.pos.x);
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outcodeOut == outcode0)
			{
				auto lerpedVertex = LerpVertex(v1, v2, t);
				v1 = lerpedVertex;
				outcode0 = ComputeOutCode(v1.pos.x, v1.pos.y);
			}
			else
			{
				auto lerpedVertex = LerpVertex(v1, v2, t);
				v2 = lerpedVertex;
				outcode1 = ComputeOutCode(v2.pos.x, v2.pos.y);
			}
		}
	}
	return accept;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (!mClipping)
		return true;

	auto* viewport = Viewport::Get();

	float maxX = viewport->GetMaxX();
	float minX = viewport->GetMinX();
	float maxY = viewport->GetMaxY();
	float minY = viewport->GetMinY();

	bool isClipping = false;
	Vertex tempVertex;

	std::vector<Vertex> inputs = vertices; // Store all our vertices before modifying them when clipping
	vertices.clear(); // Clear final buffer to receive clipped vertices

	for (auto i = 0; i < inputs.size(); ++i)
	{
		size_t safeIndex = (i + 1 >= inputs.size()) ? 0 : i + 1;

		Vertex& v1 = inputs[i];
		Vertex& v2 = inputs[safeIndex];

		float x1 = v1.pos.x;
		float x2 = v2.pos.x;

		if (x1 <= minX && x2 <= minX)
		{
			// Do nothing
		}
		else if (x1 > minX && x2 > minX)
		{
			vertices.push_back(v2);
			isClipping = true;
		}
		else if (x1 <= minX && x2 > minX)
		{
			tempVertex = LerpVertex(v1, v2, (minX - x1) / (x2 - x1));
			vertices.push_back(tempVertex);
			vertices.push_back(v2);
			isClipping = true;
		}
		else
		{
			tempVertex = LerpVertex(v2, v1, (minX - x2) / (x1 - x2));
			vertices.push_back(tempVertex);
			isClipping = true;
		}
	}

	inputs = vertices;
	vertices.clear();

	for (auto i = 0; i < inputs.size(); ++i)
	{
		size_t safeIndex = (i + 1 >= inputs.size()) ? 0 : i + 1;

		Vertex& v1 = inputs[i];
		Vertex& v2 = inputs[safeIndex];

		float y1 = v1.pos.y;
		float y2 = v2.pos.y;

		if (y1 >= maxY && y2 >= maxY)
		{
			// Do nothing
		}
		else if (y1 < maxY && y2 < maxY)
		{
			vertices.push_back(v2);
			isClipping = true;
		}
		else if (y1 >= maxY && y2 < maxY)
		{
			tempVertex = LerpVertex(v2, v1, (maxY - y2) / (y1 - y2));
			vertices.push_back(tempVertex);
			vertices.push_back(v2);
			isClipping = true;
		}
		else
		{
			tempVertex = LerpVertex(v1, v2, (maxY - y1) / (y2 - y1));
			vertices.push_back(tempVertex);
			isClipping = true;
		}
	}

	inputs = vertices;
	vertices.clear();

	for (auto i = 0; i < inputs.size(); ++i)
	{
		size_t safeIndex = (i + 1 >= inputs.size()) ? 0 : i + 1;

		Vertex& v1 = inputs[i];
		Vertex& v2 = inputs[safeIndex];

		float x1 = v1.pos.x;
		float x2 = v2.pos.x;

		if (x1 >= maxX && x2 >= maxX)
		{
			// Do nothing
		}
		else if (x1 < maxX && x2 < maxX)
		{
			vertices.push_back(v2);
			isClipping = true;
		}
		else if (x1 >= maxX && x2 < maxX)
		{
			tempVertex = LerpVertex(v2, v1, (maxX - x2) / (x1 - x2));
			vertices.push_back(tempVertex);
			vertices.push_back(v2);
			isClipping = true;
		}
		else
		{
			tempVertex = LerpVertex(v1, v2, (maxX - x1) / (x2 - x1));
			vertices.push_back(tempVertex);
			isClipping = true;
		}
	}

	inputs = vertices;
	vertices.clear();

	for (auto i = 0; i < inputs.size(); ++i)
	{
		size_t safeIndex = (i + 1 >= inputs.size()) ? 0 : i + 1;

		Vertex& v1 = inputs[i];
		Vertex& v2 = inputs[safeIndex];

		float y1 = v1.pos.y;
		float y2 = v2.pos.y;

		if (y1 <= minY && y2 <= minY)
		{
			// Do nothing
		}
		else if (y1 > minY && y2 > minY)
		{
			vertices.push_back(v2);
			isClipping = true;
		}
		else if (y1 <= minY && y2 > minY)
		{
			tempVertex = LerpVertex(v1, v2, (minY - y1) / (y2 - y1));
			vertices.push_back(tempVertex);
			vertices.push_back(v2);
			isClipping = true;
		}
		else
		{
			tempVertex = LerpVertex(v2, v1, (minY - y2) / (y1 - y2));
			vertices.push_back(tempVertex);
			isClipping = true;
		}
	}

	return isClipping;
}
