#pragma once

#include "Scene.h"

class Level1Intro : public Scene
{
public:
	Level1Intro(Graphics& gfx, GameState& gs)
		:
		Scene(gfx, "Level1Intro", gs)
	{}
	virtual void UpdateScene(Keyboard& kbd, Mouse& mouse, double dt, int& CurrentScene) override
	{
		timer += dt;
		if (timer > 2.0)
			CurrentScene = 2;
	}
	virtual void DrawFrame() override
	{
		pipeline.Clear();

		pipeline.DrawText_(V2i{ 300,200 }, font, "Level 1", Red);

		pipeline.Present();
	}
	virtual void InitializeScene() override
	{

	}
private:
	Font font{ "Font", V2i(32, 3), V2i(12, 20), ' ', '~' };
	double timer = 0.0;
};