#include "MatrixStack.h"

MatrixStack* MatrixStack::Get()
{
	static MatrixStack sInstance;
	return &sInstance;
}

void MatrixStack::OnNewFrame()
{
	mMatrices.clear();
	mCombinedTransform = {};
}

void MatrixStack::PushTranslation(Vector3 d)
{
	mMatrices.push_back(Matrix4::Translation(d));
	CalculateMatrix();
}

void MatrixStack::PushRotationX(float radian)
{
	mMatrices.push_back(Matrix4::RotationX(radian));
	CalculateMatrix();
}

void MatrixStack::PushRotationY(float radian)
{
	mMatrices.push_back(Matrix4::RotationY(radian));
	CalculateMatrix();
}

void MatrixStack::PushRotationZ(float radian)
{
	mMatrices.push_back(Matrix4::RotationZ(radian));
	CalculateMatrix();
}

void MatrixStack::PushScaling(Vector3 s)
{
	mMatrices.push_back(Matrix4::Scaling(s));
	CalculateMatrix();
}

void MatrixStack::PopMatrix()
{
	mMatrices.pop_back();
	CalculateMatrix();
}

void MatrixStack::CalculateMatrix()
{
	Matrix4 calculateMatrix = Matrix4::Identity();

	for (auto it = std::rbegin(mMatrices); it != std::rend(mMatrices); ++it)
	{
		calculateMatrix = calculateMatrix * (*it);
	}
	
	mCombinedTransform = calculateMatrix;
}
