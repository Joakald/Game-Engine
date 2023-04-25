#pragma once

#include "Graphics.h"
#include <memory>
#include <vector>
#include "GameState.h"

#include "StartMenu.h"
#include "Level1Intro.h"
#include "Level1Room1.h"
#include "GameOver.h"
#include "Level1Outro.h"

class GameController
{
public:
	GameController(HWND in_hwnd, int in_width, int in_height)
		:
		gfx(in_hwnd, in_width, in_height)
	{
		/*
		Scenes.push_back(std::make_unique<Scene1>(gfx, gs));
		Scenes.push_back(std::make_unique<Scene2>(gfx, gs));
		Scenes.push_back(std::make_unique<Scene3>(gfx, gs));
		Scenes.push_back(std::make_unique<Scene4>(gfx, gs));
		Scenes.push_back(std::make_unique<Scene5>(gfx, gs));
		*/
		Scenes.push_back(std::make_unique<StartMenu>(gfx, gs));
		Scenes.push_back(std::make_unique<Level1Intro>(gfx, gs));
		Scenes.push_back(std::make_unique<Level1Room1>(gfx, gs));
		Scenes.push_back(std::make_unique<Level1Outro>(gfx, gs));
		Scenes.push_back(std::make_unique<GameOver>(gfx, gs));
		CurrentScene = 0;
		LastScene = 0;
	}
	void UpdateGame(Keyboard& kbd, Mouse& mouse, double dt)
	{
		if (CurrentScene != LastScene)
		{
			(*Scenes[CurrentScene]).InitializeScene();
			LastScene = CurrentScene;
		}
		(*Scenes[CurrentScene]).UpdateScene(kbd, mouse, dt, CurrentScene);
	}
	void DrawFrame()
	{
		(*Scenes[CurrentScene]).DrawFrame();
	}
private:
	Graphics gfx;
	std::vector<std::unique_ptr<Scene>> Scenes;
	GameState gs;
	int CurrentScene;
	int LastScene;
	double timer = 0.0;
};