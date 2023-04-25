#pragma once
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include "BaseGeometry.h"
#include "Windows.h"

class Texture
{
public:
	Texture(std::string texture_name, V2i in_pic_dim)
		:
		name(texture_name),
		pic_dim(in_pic_dim)
	{
		std::ifstream texture_file("Texture/" + texture_name + ".bmp", std::ios::binary);

		assert(texture_file);

		BITMAPFILEHEADER bmFileHeader;
		texture_file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

		BITMAPINFOHEADER bmInfoHeader;
		texture_file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

		assert(bmInfoHeader.biBitCount == 24);
		assert(bmInfoHeader.biCompression == BI_RGB);

		const int width = bmInfoHeader.biWidth;
		const int height = bmInfoHeader.biHeight;
		const int padding = (4 - width % 4) % 4;

		texture_file.seekg(bmFileHeader.bfOffBits);
		tex = std::vector<Color>(width * height);

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				tex[y * width + x] = Color(
					texture_file.get(), texture_file.get(),
					texture_file.get(), 50u);
			}
			texture_file.seekg(padding, std::ios::cur);
		}

		dim.x = width;
		dim.y = height;
	}
public:
	std::string name;
	V2i dim;
	V2i pic_dim;
	std::vector<Color> tex;
};