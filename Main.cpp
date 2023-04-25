#include "Window.h"
#include "GameController.h"
#include "HPTimer.h"

int WINAPI wWinMain(HINSTANCE HandleToExe, HINSTANCE null, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window WND(HandleToExe, "Burre's Window", 800, 600);
		try
		{
			GameController GC(WND.HandleToWindow, WND.GetWidth(), WND.GetHeight());
			HPTimer HPT;

			while (WND.ProcessMessages())
			{
				HPT.UpdateTime();
				WND.UpdateTitle((int)(1.0 / HPT.GetTimeDelta()));

				GC.UpdateGame(WND.GetKeyboard(), WND.GetMouse(), HPT.GetTimeDelta());
				GC.DrawFrame();
			}
		}
		catch (std::exception& e)
		{
			WND.ShowMessageBox(e.what());
		}
	}
	catch (...)
	{
		MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK);
	}
	return 0;
}