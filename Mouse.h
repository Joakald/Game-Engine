#pragma once

#include "Vertex.h"

class Mouse
{
public:
	Mouse() = default;
	Mouse(const Mouse& src) = delete;
	Mouse& operator=(const Mouse& src) = delete;
	~Mouse() {}
// getters & setters
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}
	V2d GetXY()
	{
		return V2d((double)x,(double)y);
	}
	bool LeftIsPressed()
	{
		return LeftIsPressedBool;
	}
	bool RightIsPressed()
	{
		return RightIsPressedBool;
	}
	bool IsInWindow()
	{
		return IsInWindowBool;
	}
	void OnMouseMove(int new_x, int new_y)
	{
		x = new_x; y = new_y;
	}
	void OnMouseEnter()
	{
		IsInWindowBool = true;
	}
	void OnMouseLeave()
	{
		IsInWindowBool = false;
	}
	void OnLeftPressed()
	{
		LeftIsPressedBool = true;
	}
	void OnLeftReleased()
	{
		LeftIsPressedBool = false;
	}
	void OnRightPressed()
	{
		RightIsPressedBool = true;
	}
	void OnRightReleased()
	{
		RightIsPressedBool = false;
	}
private:
	int x{};
	int y{};
	bool LeftIsPressedBool = false;
	bool RightIsPressedBool = false;
	bool IsInWindowBool = false;
};