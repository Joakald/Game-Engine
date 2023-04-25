#pragma once

#include "Vertex.h"

struct Color
{
	Color()	
	{
		red = 0u;
		green = 0u;
		blue = 0u;
		alpha = 0u;
	}
	Color(char in_red, char in_green, char in_blue, char in_alpha)
		:
		red(in_red),
		green(in_green),
		blue(in_blue),
		alpha(in_alpha)
	{}
	Color(int in_c)
	{
		alpha = in_c << 24u;
		red = in_c << 16u;
		green = in_c << 8u;
		blue = in_c;
	}
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
	Color& operator=(const Color& src)
	{
		red = src.red;
		green = src.green;
		blue = src.blue;
		alpha = src.alpha;
		return *this;
	}
	Color operator*(const double& scalar)
	{
		assert(scalar >= 0.0);
		assert(scalar <= 1.0);
		red *= scalar;
		green *= scalar;
		blue *= scalar;
		return *this;
	}
	Color operator+(const Color& src)
	{
		red += src.red;
		green += src.green;
		blue += src.blue;
		assert(red >= 0u && red <= 255u);
		assert(green >= 0u && green <= 255u);
		assert(blue >= 0u && blue <= 255u);
		return *this;
	}
	bool operator==(const Color& src) const
	{
		if (src.red == red
			&& src.green == green
			&& src.blue == blue)
			return true;
		else
			return false;
	}
	bool operator!=(const Color& src) const
	{
		if (!(*this == src))
			return true;
		else
			return false;
	}
};

// using const outside a class scope is the same as using
// static const within a class scope
const Color White = Color(255u,255u,255u,255u );
const Color Red = Color( 255u,0u,0u, 255u);
const Color Green = Color( 0u,255u,0u, 255u);
const Color Blue = Color( 0u,0u,255u, 100u);
const Color DarkGrey = Color( 30u,30u,30u, 255u);
const Color LightGrey = Color( 80u,80u,80u, 255u);
const Color Purple = Color(255u, 0u, 255u, 255u);
const Color Yellow = Color(255u, 255u, 0u, 255u);
const Color Black = Color(0u, 0u, 0u, 255u);

struct Point
{
	Point(V2d in_v1, V2d in_dir, double in_speed, Color in_c)
		: 
		v1(in_v1),
		dir(in_dir),
		speed(in_speed),
		c(in_c)
	{}

	V2d v1;
	V2d dir;
	double speed;
	Color c;
};

struct Line
{
	Line(V2d in_v1, V2d in_v2, V2d in_dir, double in_speed, Color in_c)
		:
		v1(in_v1),
		v2(in_v2),
		dir(in_dir),
		speed(in_speed),
		c(in_c)
	{}
	V2d v1;
	V2d v2;
	V2d dir;
	double speed;
	Color c;
};

struct Triangle2d
{
	Triangle2d(V2d in_v1, V2d in_v2, V2d in_v3, V2d in_dir, double in_speed, Color in_c)
		:
		v1(in_v1),
		v2(in_v2),
		v3(in_v3),
		dir(in_dir),
		speed(in_speed),
		c(in_c)
	{}
	V2d v1;
	V2d v2;
	V2d v3;
	V2d dir;
	double speed;
	Color c;
};

class Rect
{
public:
	Rect(V2d in_pos, int in_width, int in_height, Color in_c)
		:
		pos(in_pos),
		width(in_width),
		height(in_height),
		c(in_c)
	{}
	V2d pos;
	int width;
	int height;
	Color c;
};

struct Circle
{
	Circle(V2d in_center, V2d in_dir, double in_radius, double in_speed, Color in_c)
		:
		center(in_center),
		dir(in_dir),
		radius(in_radius),
		speed(in_speed),
		c(in_c)
	{}
	V2d center;
	V2d dir;
	double radius;
	double speed;
	Color c;
};

struct Triangle3d
{
	Triangle3d(V3d in_v1, V3d in_v2, V3d in_v3, V3d in_dir, double in_speed, Color in_c)
		:
		v1(in_v1),
		v2(in_v2),
		v3(in_v3),
		dir(in_dir),
		speed(in_speed),
		c(in_c)
	{}
	V3d v1;
	V3d v2;
	V3d v3;
	V3d dir;
	double speed;
	Color c;
};