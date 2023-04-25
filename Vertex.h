#pragma once

#include <cmath>
#include <assert.h>

template<class T>
class Vertex2d
{
public:
	// constructors
	Vertex2d() {}
	Vertex2d(T in_x, T in_y)
		:
		x(in_x),
		y(in_y)
	{}
	// operators
	Vertex2d operator=(const Vertex2d& src)
	{
		x = src.x; y = src.y;
		return *this;
	}
	Vertex2d operator+(const Vertex2d& src)
	{
		return Vertex2d(x + src.x, y + src.y);
	}
	Vertex2d operator-(const Vertex2d& src)
	{
		return Vertex2d(x - src.x, y - src.y);
	}
	Vertex2d operator*(const T& scalar)
	{
		return Vertex2d(x * scalar, y * scalar);
	}
	Vertex2d operator/(const T& scalar)
	{
		return Vertex2d(x / scalar, y / scalar);
	}
	Vertex2d operator+=(const Vertex2d& src)
	{
		x += src.x; y += src.y;
		return *this;
	}
	Vertex2d operator-=(const Vertex2d& src)
	{
		x -= src.x; y -= src.y;
		return *this;
	}
	Vertex2d operator*=(const Vertex2d& src)
	{
		x *= src.x; y *= src.y;
		return *this;
	}
	Vertex2d operator/=(const Vertex2d& src)
	{
		x /= src.x; y /= src.y;
		return *this;
	}
	Vertex2d operator/=(const T& scalar)
	{
		x /= scalar; y /= scalar;
		return *this;
	}
	bool operator==(const Vertex2d src)
	{
		if (x == src.x && y == src.y)
			return true;
		else
			return false;
	}
	bool operator!=(const Vertex2d src)
	{
		if (x == src.x && y == src.y)
			return false;
		else
			return true;
	}
	bool operator>(const Vertex2d src)
	{
		if (x > src.x && y > src.y)
			return true;
		else
			return false;
	}
	bool operator<(const Vertex2d src)
	{
		if (x < src.x && y < src.y)
			return true;
		else
			return false;
	}
	double operator*(const Vertex2d& src)
	{
		return x * src.x + y * src.y;
	}
public:
	Vertex2d Scale(T scalar)
	{
		return Vertex2d(x * scalar, y * scalar);
	}
	double GetDistance(const Vertex2d& src)
	{
		return std::sqrt(std::pow(x - src.x, 2) + std::pow(y - src.y, 2));
	}
public:
	T x{};
	T y{};
};
typedef Vertex2d<int> V2i;
typedef Vertex2d<double> V2d;

template<class T>
class Vertex3d
{
public:
	// constructors
	Vertex3d(T in_x, T in_y, T in_z)
		:
		x(in_x),
		y(in_y),
		z(in_z)
	{}
	// operators
	Vertex3d operator=(const Vertex3d& src)
	{
		x = src.x; y = src.y; z = src.z;
		return *this;
	}
	Vertex3d operator+(const Vertex3d& src)
	{
		x += src.x; y += src.y; z += src.z;
		return *this;
	}
	Vertex3d operator-(const Vertex3d& src)
	{
		x -= src.x; y -= src.y; z -= src.z;
		return *this;
	}
	Vertex3d operator*(const T& scalar)
	{
		return Vertex3d(x * scalar, y * scalar, z * scalar);
	}
	bool operator==(const Vertex3d src)
	{
		if (x == src.x && y == src.y && z == src.z)
			return true;
		else
			return false;
	}
	bool operator!=(const Vertex3d src)
	{
		if (x == src.x && y == src.y && z == src.z)
			return false;
		else
			return true;
	}
	double operator*(const Vertex3d& src)
	{
		return x * src.x + y * src.y + z * src.z;
	}
public:
	Vertex3d Scale(T scalar)
	{
		return Vertex3d(x * scalar, y * scalar, z * scalar);
	}
	double GetDistance(const Vertex3d& src)
	{
		return std::sqrt(std::pow(x - src.x, 2) + std::pow(y - src.y, 2) + std::pow(z - src.z, 2));
	}
	Vertex3d CrossProduct(const Vertex3d& src)
	{
		T new_x(y * src.z - z * src.y);
		T new_y(z * src.x - x * src.z);
		T new_z(x * src.y - y * src.x);
		return Vertex3d(new_x, new_y, new_z);
	}
public:
	T x{};
	T y{};
	T z{};
};
typedef Vertex3d<int> V3i;
typedef Vertex3d<double> V3d;