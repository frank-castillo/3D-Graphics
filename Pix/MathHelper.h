#pragma once
#include <cmath>

#include "Matrix4.h"
#include "Vector3.h"

// Vector3 Math
float MagnitudeSquared(Vector3 v);
float Magnitude(Vector3 v);
float Dot(Vector3 a, Vector3 b);
Vector3 Normalize(Vector3 v);
Vector3 Cross(Vector3 a, Vector3 b);

// Matrix4 Math
Vector3 TransformCoord(Vector3 v, Matrix4 m); // assume w = 1 Vector3 TransformNormal(Vector3 v, Matrix4 m); // assume w = 0 float Determinant(Matrix4 m);
Vector3 TransformNormal(Vector3 v, Matrix4 m); // assume w = 0
float Determinant(Matrix4 m);
Matrix4 Adjoint(Matrix4 m);
Matrix4 Transpose(Matrix4 m);
Matrix4 Inverse(Matrix4 m);