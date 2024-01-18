#pragma once

struct Vector3
{
	float x, y, z;
	constexpr Vector3() noexcept : Vector3(0.0f) {};
	constexpr explicit Vector3(float f) noexcept : Vector3(f, f, f) {};
	constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

	static Vector3 Zero() { return Vector3(); }
	static Vector3 One() { return Vector3(1.0f, 1.0f, 1.0f); }
	static Vector3 XAxis() { return Vector3(1.0f, 0.0f, 0.0f); }
	static Vector3 YAxis() { return Vector3(0.0f, 1.0f, 0.0f); }
	static Vector3 ZAxis() { return Vector3(0.0f, 0.0f, 1.0f); }

	// operator unary - (const)
	// operator binary +=*/ (const)
	constexpr Vector3 operator-() const
	{
		return {-x, -y, -z };
	}

	constexpr Vector3 operator+(const Vector3& v)const
	{
		return { x + v.x, y + v.y, z + v.z };
	}

	constexpr Vector3 operator-(const Vector3& v)const
	{
		return { x - v.x, y - v.y, z - v.z };
	}

	constexpr Vector3 operator*(const float rhs)const
	{
		return { x * rhs, y * rhs, z * rhs };
	}

	constexpr Vector3 operator/(const float rhs)const
	{
		return { x / rhs, y / rhs, z / rhs };
	}

	// self assign +=, -+, *=, /=
	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	Vector3& operator/=(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	bool operator==(const Vector3& v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z);
	}
};