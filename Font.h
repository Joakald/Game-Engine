#pragma once
# include "Vertex.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <vector>
#include "BaseGeometry.h"

class Font
{
public:
	Font(std::string name_in, V2i dim_in, V2i char_dim_in, char first_char_in, char last_char_in)
		:
		name(name_in),
		dim(dim_in),
		char_dim(char_dim_in),
		first_char(first_char_in),
		last_char(last_char_in)
	{
		std::ifstream font_file("Texture/" + name + ".bmp", std::ios::binary);

		assert(font_file);

		BITMAPFILEHEADER bmFileHeader;
		font_file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

		BITMAPINFOHEADER bmInfoHeader;
		font_file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));
		
		const int width = bmInfoHeader.biWidth;
		const int height = bmInfoHeader.biHeight;
		const int padding = (4 - width % 4) % 4;	

		font_file.seekg(bmFileHeader.bfOffBits);

		font = std::vector<Color>(width * height);

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				font[y * width + x] = Color(
					font_file.get(), font_file.get(),
					font_file.get(), 0);
			}
			font_file.seekg(padding, std::ios::cur);
		}

		assert(font.size() == (dim.x * char_dim.x) * (dim.y * char_dim.y));
	}
public:
	std::string name;
	V2i dim;
	V2i char_dim;
	char first_char;
	char last_char;
	std::vector<Color> font;
};