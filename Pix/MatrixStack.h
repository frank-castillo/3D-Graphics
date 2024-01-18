#pragma once
#include <XEngine.h>

#include "MathHelper.h"

class MatrixStack
{
public:
	static MatrixStack* Get();

public:
	void OnNewFrame();
	void PushTranslation(Vector3 d);
	void PushRotationX(float radian);
	void PushRotationY(float radian);
	void PushRotationZ(float radian);
	void PushScaling(Vector3 s);
	void PopMatrix();
	Matrix4 GetTransform() const { return mCombinedTransform; }

private:
	std::vector<Matrix4> mMatrices; // History
	Matrix4 mCombinedTransform;
	void CalculateMatrix();
};

