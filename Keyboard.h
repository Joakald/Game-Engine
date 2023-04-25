#pragma once
#include<vector>

class Keyboard
{
public:
	Keyboard()
		:
		keystates(std::vector<bool>(256, false))
	{}
	void OnKeyPressed(char keycode)
	{
		keystates[keycode] = true;
	}
	void OnKeyReleased(char keycode)
	{
		keystates[keycode] = false;
	}
	bool KeyIsPressed(char keycode)
	{
		if (keystates[keycode] == true)
			return true;
		else
			return false;
	}
private:
	static constexpr int nKeys = 256;
	std::vector<bool> keystates;
};