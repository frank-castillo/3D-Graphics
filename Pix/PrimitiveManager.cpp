#include "PrimitiveManager.h"

#include "Clipper.h"
#include "MatrixStack.h"
#include "PixCamera.h"
#include "Rasterizer.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		float hw = gResolutionX * 0.5f;
		float hh = gResolutionY * 0.5f;

		return
		{
			hw, 0,  0, 0,
			0,  -hh,0, 0,
			0,  0,  1, 0,
			hw, hh, 0, 1
		};
	}

	bool IsNDCBackface(Vector3 a, Vector3 b, Vector3 c)
	{
		Vector3 ab = b - a;
		Vector3 ac = c - a;
		Vector3 normal = Normalize(Cross(ab, ac));
		return normal.z > 0.0f;
	}
}

PrimitiveManager* PrimitiveManager::Get()
{
	static PrimitiveManager sInstance;
	return &sInstance;
}

bool PrimitiveManager::BeginDraw(Topology topology, bool applyTransform)
{
	if (mDrawBegin == true)
	{
		return false;
	}

	mVertexBuffer.clear();
	mTopology = topology;
	mApplyTransform = applyTransform;
	mDrawBegin = true;

	return true;
}

void PrimitiveManager::AddVertex(Vertex vertex)
{
	if (mDrawBegin == true)
	{
		mVertexBuffer.push_back(vertex);
	}
}

bool PrimitiveManager::EndDraw()
{
	if (mDrawBegin == false)
	{
		return false; // Call end draw before begin draw
	}

	switch (mTopology)
	{
	case Topology::Point:
	{
		if (mApplyTransform)
		{
			Matrix4 matWorld = MatrixStack::Get()->GetTransform();
			Matrix4 matView = PixCamera::Get()->GetViewMatrix();
			Matrix4 matProj = PixCamera::Get()->GetProjectionMatrix();
			Matrix4 matScreen = GetScreenTransform();
			Matrix4 matFinal = matWorld * matView * matProj * matScreen;
			for (auto& v : mVertexBuffer)
			{
				auto posScreen = TransformCoord(v.pos, matFinal);
				v.pos = posScreen;
			}
		}

		for (int i = 0; i < mVertexBuffer.size(); ++i)
		{
			auto v = mVertexBuffer[i];
			if (Clipper::Get()->ClipPoint(v))
			{
				Rasterizer::Get()->DrawPoint(v);
			}
		}
		break;
	}
	case Topology::Line:
	{
		if (mApplyTransform)
		{
			Matrix4 matWorld = MatrixStack::Get()->GetTransform();
			Matrix4 matView = PixCamera::Get()->GetViewMatrix();
			Matrix4 matProj = PixCamera::Get()->GetProjectionMatrix();
			Matrix4 matScreen = GetScreenTransform();
			Matrix4 matFinal = matWorld * matView * matProj * matScreen;
			for (auto& v : mVertexBuffer)
			{
				auto posScreen = TransformCoord(v.pos, matFinal);
				v.pos = posScreen;
			}
		}

		for (int i = 0; i + 1 < mVertexBuffer.size(); i += 2)
		{
			auto v1 = mVertexBuffer[i];
			auto v2 = mVertexBuffer[i + 1];
			if (Clipper::Get()->ClipLine(v1, v2))
			{
				Rasterizer::Get()->DrawLine(v1, v2);
			}
		}
		break;
	}
	case Topology::Triangle:
	{
		if (mVertexBuffer.size() >= 3)
		{ 
			std::vector<Vertex> triangles;

			if (mApplyTransform)
			{
				Matrix4 matWorld = MatrixStack::Get()->GetTransform();
				Matrix4 matView = PixCamera::Get()->GetViewMatrix();
				Matrix4 matProj = PixCamera::Get()->GetProjectionMatrix();
				Matrix4 matScreen = GetScreenTransform();

				Matrix4 matLocalToScreen = matWorld * matView * matProj * matScreen;
				Matrix4 matLocalToNDC = matWorld * matView * matProj; // X [-1,1], y [-1,1], z [0,1]
				Matrix4 matNDCToScreen = matScreen; // X [0,screenW], y [0,screenH], z [0,1]
				//Matrix4 viewToScreen = toNDC * matScreen;
				//Matrix4 matLocalToNDC = matWorld * matView * matProj;
				//Matrix4 matNDCToScreen = matScreen;
				

				for (size_t i = 0; i < mVertexBuffer.size(); i += 3)
				{
					auto a = mVertexBuffer[i];
					auto b = mVertexBuffer[i + 1];
					auto c = mVertexBuffer[i + 2];

					auto aLocalPos = a.pos;
					auto bLocalPos = b.pos;
					auto cLocalPos = c.pos;

					auto aNDCPos = TransformCoord(aLocalPos, matLocalToNDC);
					auto bNDCPos = TransformCoord(bLocalPos, matLocalToNDC);
					auto cNDCPos = TransformCoord(cLocalPos, matLocalToNDC);

					if (mCullMode == CullMode::Back && IsNDCBackface(aNDCPos, bNDCPos, cNDCPos))
						continue;
					else if (mCullMode == CullMode::Front && !IsNDCBackface(aNDCPos, bNDCPos, cNDCPos))
						continue;

					a.pos = TransformCoord(aLocalPos, matLocalToScreen);
					b.pos = TransformCoord(bLocalPos, matLocalToScreen);
					c.pos = TransformCoord(cLocalPos, matLocalToScreen);

					triangles.push_back(a);
					triangles.push_back(b);
					triangles.push_back(c);
				}
			}
			else
			{
				triangles = mVertexBuffer;
			}

			for (int i = 0; i + 2 < triangles.size(); i += 3)
			{
				std::vector<Vertex> polygon;
				polygon.push_back(triangles[i]);
				polygon.push_back(triangles[i + 1]);
				polygon.push_back(triangles[i + 2]);
				if (Clipper::Get()->ClipTriangle(polygon))
				{
					for (int j = 2; j < polygon.size(); ++j)
					{
						Rasterizer::Get()->DrawTriangle(polygon[0], polygon[j - 1], polygon[j]);
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}

	mDrawBegin = false;

	return false;
}

void PrimitiveManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}
