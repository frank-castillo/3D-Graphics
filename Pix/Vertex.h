#pragma once
#include <XEngine.h>

#include "Vector3.h"
	
struct Vertex
{
	Vector3 pos;
	X::Color color;	
};

inline Vector3 LerpPosition(Vector3 a, Vector3 b, float t)
{
	return a + (b - a) * t;
}
inline X::Color LerpColor(X::Color a, X::Color b, float t)
{
	return a + (b - a) * t;
}
inline Vertex LerpVertex(Vertex a, Vertex b, float t)
{
	return
	{
		LerpPosition(a.pos, b.pos,t),
		LerpColor(a.color, b.color, t)
	};
}
