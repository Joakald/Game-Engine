#pragma once

#include "Windows.h"
#include "ErrorHandling.h"
#include "BaseGeometry.h"

class Graphics
{
public:
	// constructors
	Graphics(HWND in_hwnd, int in_width, int in_height)
		:
		hwnd(in_hwnd),
		width(in_width),
		height(in_height)
	{
		hdc = GetDC(hwnd);
		hmdc = CreateCompatibleDC(hdc);
	}
	Graphics(const Graphics& src) = delete;
	~Graphics()
	{
		DeleteDC(hmdc);
		ReleaseDC(hwnd, hdc);
	}
	// operators
	Graphics operator=(const Graphics& src) = delete;
public:
	void Clear()
	{
		frame = (int*)calloc(width * height, sizeof(int));
	}
	void SetPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		frame[width * y + x] = int((alpha << 24u) | (red << 16u) | (green << 8u) | blue);
	}
	Color GetPixel(int x, int y)
	{
		return frame[y * width + x];
	}
	void Present()
	{	
		// create bitmap frame
		HBITMAP bmp = CreateBitmap(width, height, 1, 32, (void*)frame);

		// display
		SelectObject(hmdc, bmp);
		BitBlt(hdc, 0, 0, width, height, hmdc, 0, 0, SRCCOPY);
		DeleteObject(bmp);

		// empty the frame
		free(frame);
		frame = nullptr;
	}
private:
	HWND hwnd;
	HDC hdc;
	HDC hmdc;
	int* frame = nullptr;
	int width;
	int height;
};