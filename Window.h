#pragma once

#include "Windows.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <string>

class Window
{
public:
	// constructors
	Window(HINSTANCE in_HandleToExe, std::string in_window_title, int in_width, int in_height)
		:
		HandleToExe(in_HandleToExe),
		window_title(in_window_title),
		width(in_width),
		height(in_height)
	{
		// register class
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = WindowProcedure; // pass a pointer to a static member function which then delegates to a non-static message handler
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = HandleToExe;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = L"BurreWindowClass";
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);

		RECT rect = { 0,0,in_width,in_height };
		AdjustWindowRectEx(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false, NULL);

		// create window instance
		HandleToWindow = CreateWindowEx(
			NULL,
			L"BurreWindowClass",
			NULL,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			50, 50,
			rect.right - rect.left, rect.bottom - rect.top,
			nullptr,
			nullptr,
			in_HandleToExe,
			this);

		// display window
		ShowWindow(HandleToWindow, SW_SHOWDEFAULT);
	}
	Window(Window& src) = delete;
	~Window()
	{
		UnregisterClass(L"BurreGameWindow", HandleToExe);
	}
	// operators
	Window operator=(Window& src) = delete;
	// getters
	int GetWidth()
	{
		return width;
	}
	int GetHeight()
	{
		return height;
	}
	Keyboard& GetKeyboard()
	{
		return kbd;
	}
	Mouse& GetMouse()
	{
		return mouse;
	}
public:
	bool ProcessMessages()
	{
		MSG msg = {};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) return false;
		}
		return true;
	}
	void UpdateTitle(int fps)
	{
		std::string MousePosition;
		if (mouse.IsInWindow())
		{
			MousePosition = ", Mouse Position: (" + std::to_string(mouse.GetX()) + "," + std::to_string(mouse.GetY()) + ")";
		}
		else
		{
			MousePosition = ", Mouse Position: Outside of Window";
		}
		std::string str = window_title + ", FPS: " + std::to_string(fps) + MousePosition;
		SetWindowTextA(HandleToWindow, str.c_str());
	}
	void ShowMessageBox(std::string message)
	{
		std::wstring wmessage = StringToWString(message);
		MessageBox(HandleToWindow, wmessage.c_str(), L"Error", MB_OK);
	}
	std::wstring StringToWString(const std::string& s)
	{
		std::wstring temp(s.length(), L' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp;
	}
	static LRESULT CALLBACK WindowProcedure(HWND HandleToWindow, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* pWindow = nullptr;
		if (msg == WM_NCCREATE)
		{
			// extract the pointer to the window from the message
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pWindow = (Window*)pCreate->lpCreateParams;

			// store the pointer in the instance data for the window
			SetWindowLongPtr(HandleToWindow, GWLP_USERDATA, (LONG_PTR)pWindow);
			
			pWindow->HandleToWindow = HandleToWindow;
		}
		else
		{
			// get the instance data
			pWindow = (Window*)GetWindowLongPtr(HandleToWindow, GWLP_USERDATA);
		}
		if (pWindow != nullptr)
		{
			// call the message handler by using the pointer
			return pWindow->MessageHandler(msg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(HandleToWindow, msg, wParam, lParam);
		}
	}
	LRESULT CALLBACK MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// update keyboard and mouse objects based on the message 
		char keycode = static_cast<unsigned char>(wParam);
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			kbd.OnKeyPressed(keycode);
			break;
		case WM_KEYUP:
			kbd.OnKeyReleased(keycode);
			break;
		case WM_MOUSEMOVE:
			POINTS mp = MAKEPOINTS(lParam);
			if (mp.x >= 0 && mp.y >= 0
				&& mp.x < width && mp.y < height)
			{
				mouse.OnMouseMove(mp.x, mp.y);
				if (!mouse.IsInWindow())
				{
					SetCapture(HandleToWindow);
					mouse.OnMouseEnter();
				}
			}
			else
			{
				mouse.OnLeftReleased();
				mouse.OnRightReleased();
				if (mouse.IsInWindow())
				{
					ReleaseCapture();
					mouse.OnMouseLeave();
				}

			}
			break;
		case WM_LBUTTONDOWN:
			mouse.OnLeftPressed();
			break;
		case WM_LBUTTONUP:
			mouse.OnLeftReleased();
			break;
		case WM_RBUTTONDOWN:
			mouse.OnRightPressed();
			break;
		case WM_RBUTTONUP:
			mouse.OnRightReleased();
			break;
		}

		return DefWindowProc(HandleToWindow, msg, wParam, lParam);
	}
public:
	HINSTANCE HandleToExe = nullptr;
	HWND HandleToWindow = nullptr;
private:	
	Keyboard kbd;
	Mouse mouse;
	std::string window_title;
	int width;
	int height;
};