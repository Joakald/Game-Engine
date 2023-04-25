#pragma once
#pragma once

#include "Scene.h"
#include "Font.h"

class Level1Outro : public Scene
{
public:
	Level1Outro(Graphics& gfx, GameState& gs)
		:
		Scene(gfx, "Level1Outro", gs)
	{}
	virtual void UpdateScene(Keyboard& kbd, Mouse& mouse, double dt, int& CurrentScene) override
	{
		timer += dt;
		if (kbd.KeyIsPressed(VK_SPACE))
		{
			CurrentScene = 0;
			timer = 0.0;
		}
	}
	virtual void DrawFrame() override
	{
		pipeline.Clear();

		pipeline.DrawText_(V2i{ 300,200 }, font, "Level 1 Finished!/(level 1 is actually the entire game)", Red);

		if ((int)timer % 2 == 0)
			pipeline.DrawText_(V2i{ 200,400 }, font, "Press space to return to the start menu", Green);

		pipeline.Present();
	}
	virtual void InitializeScene() override
	{

	}
public:
	Font font{ "Font", V2i(32, 3), V2i(12, 20), ' ', '~' };
	double timer = 0.0;
};