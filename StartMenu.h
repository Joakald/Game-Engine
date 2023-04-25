#pragma once

#include "Scene.h"
#include "Font.h"
#include "Texture.h"

class StartMenu : public Scene
{
public:
StartMenu(Graphics& gfx, GameState& gs)
	:
	Scene(gfx, "StartMenu", gs)
{}
virtual void UpdateScene(Keyboard& kbd, Mouse& mouse, double dt, int& CurrentScene) override
{
	timer += dt;
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		CurrentScene = 1;
		timer = 0.0;
	}
}
virtual void DrawFrame() override
{
	pipeline.Clear();

	pipeline.DrawText_(V2i{ 200,100 }, font, "Welcome to the best and most/awesome game to ever exist.", Green);
	pipeline.DrawText_(V2i{ 200,200 }, font, "Instructions: Use W, A, S and D to move around/and use the mouse to shoot.", Red);
	pipeline.DrawText_(V2i{ 200,300 }, font, "To win, find the goal and avoid getting/hit by the bad guys.", Blue);

	pipeline.DrawText_(V2i{ 300,500 }, font, "Btw, that's you --->", White);

	pipeline.DrawTexture(V2d{ 600.0,500.0 }, V2i{ 32,0 }, pic_of_player);

	if ((int)timer % 2 == 0 )
		pipeline.DrawText_(V2i{ 200,400 }, font, "Press space to play.", Green);

	pipeline.Present();
}
virtual void InitializeScene() override
{

}
private:
	Font font{ "Font", V2i(32, 3), V2i(12, 20), ' ', '~' };
	Texture pic_of_player{ "player_pic", V2i{32,32} };
	double timer = 0.0;
};