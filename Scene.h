#pragma once
#include <string>
#include "Keyboard.h"
#include "Mouse.h"
#include "Pipeline.h"
#include "GameState.h"
#include "Font.h"
#include "Texture.h"

class Scene
{
public:
	Scene(Graphics& in_gfx, std::string in_name, GameState& in_gs)
		:
		pipeline(in_gfx),
		name(in_name),
		gs(in_gs)
	{}
	virtual void UpdateScene(Keyboard& kbd, Mouse& mouse, double dt, int& CurrentScene ) = 0;
	virtual void DrawFrame() = 0;
	virtual void InitializeScene() = 0;
public:
	Pipeline pipeline;
	std::string name;
	GameState& gs;
};

/*
#include "Scene.h"

class Scene : public Scene
{
public:
	Scene4(Graphics& gfx, GameState& gs)
		:
		Scene(gfx, "Scene", gs)
	{}
virtual void UpdateScene(Keyboard& kbd, Mouse& mouse, double dt, int& CurrentScene ) override
{

}
virtual void DrawFrame() override
{

}
virtual void InitializeScene() override
{

}
};
*/