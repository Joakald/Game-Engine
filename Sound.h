#pragma once
#include "Windows.h"
#include <mmsystem.h>
#include <string>
#include <vector>

class Sound
{
public:
	Sound(std::string sound_name)
		:
		name(sound_name)
	{
		std::string s = "Sound/" + name + ".wav";
		path = std::wstring(s.begin(), s.end());
	}
	void Play()
	{
		const wchar_t* wcstr = path.c_str();
		PlaySound(wcstr, NULL, SND_ASYNC | SND_NODEFAULT | SND_FILENAME);
	}
	void StopPlay()
	{
		PlaySound(NULL, 0, 0);
	}
private:
	std::string name;
	std::wstring path;
};


/*
class Sound
{
public:
	Sound()
	{}
	Sound(std::vector<std::string> sound_name)
		:
		names(in_names)
	{}
	const wchar_t* StringToCWchar_t(std::string s)
	{
		std::wstring wstr = std::wstring(s.begin(), s.end());
		const wchar_t* wcstr = wstr.c_str();
		return wcstr;
	}
	void PlayFile(std::string name)
	{
		for (std::string s : names)
		{
			if (s == name)
			{
				const wchar_t* directory = StringToCWchar_t("Sound/" + s + ".wav");
				PlaySound(directory, NULL, SND_ASYNC);
			}
		}
	}
	void PlayFile(int index)
	{
		const wchar_t* directory = StringToCWchar_t("Sound/" + names[index] + ".wav");
		PlaySound(directory, NULL, SND_ASYNC);
	}
	void PlayExtern(std::string s)
	{
		const wchar_t* directory = StringToCWchar_t("Sound/" + s + ".wav");
		PlaySound(directory, NULL, SND_ASYNC);

		PlaySound(TEXT("Sound/f2.wav"), NULL, SND_ASYNC);
	}
	void StopSound()
	{
		PlaySound(NULL, 0, 0);
	}
private:
	std::vector<std::string> names;
};
*/