#pragma once

#include "Scene.h"
#include "Olof.h"
#include "Wall.h"
#include "Player.h"
#include "Missile.h"

class Level1Room1 : public Scene
{
public:
	Level1Room1(Graphics& gfx, GameState& gs)
		:
		Scene(gfx, "Level1Room1", gs)
	{
		InitializeScene();
	}
	virtual void UpdateScene(Keyboard& kbd, Mouse& mouse, double dt, int& CurrentScene) override
	{
		// update player

		if (player.state == player.State::alive)
		{
			if (kbd.KeyIsPressed('W'))
				player.pos.y -= player.speed * dt;
			if (kbd.KeyIsPressed('S'))
				player.pos.y += player.speed * dt;
			if (kbd.KeyIsPressed('A'))
				player.pos.x -= player.speed * dt;
			if (kbd.KeyIsPressed('D'))
				player.pos.x += player.speed * dt;

			for (int i = 0; i < olofs.size(); i++)
			{
				if (olofs[i].state == olofs[i].State::alive)
					player.EnemyCollision(olofs[i]);
			}

			player.GoalCollision(goal, CurrentScene);
		}
		if (player.state == player.State::dying)
		{
			player.Dying(dt, CurrentScene);
		}
		if (player.state == player.State::finished)
		{
			player.Finishing(dt, CurrentScene);
		}

		// update olofs

		for (int i = 0; i < olofs.size(); i++)
		{
			if (olofs[i].state == olofs[i].State::alive)
			{
				olofs[i].pos += olofs[i].dir * dt;
				if (olofs[i].MissileCollision(missile))
				{
					olofs[i].state = olofs[i].State::dying;
					missile.state = missile.State::exploding;
				}
			}
			else if (olofs[i].state == olofs[i].State::dying)
			{
				olofs[i].Dying(dt);
			}
		}

		// update missile

		if (mouse.LeftIsPressed())
		{
			if (missile.state == missile.State::inactive)
			{
				missile.Activate(player.pos, mouse.GetXY());
			}
		}
		if (missile.state == missile.State::active)
		{
			missile.pos += missile.dir * dt;
		}
		if (missile.state == missile.State::exploding)
		{
			missile.Explode(dt);
		}

		// collisions
		for (int i = 0; i < olofs.size(); i++)
		{
			olofs[i].ScreenCollision();
		}

		player.ScreenCollision();
		missile.ScreenCollision();

		for (int i = 0; i < walls.size(); i++)
		{
			player.WallCollision(walls[i]);
			missile.WallCollision(walls[i]);

			for (int j = 0; j < olofs.size(); j++)
			{
				olofs[j].WallCollision(walls[i]);
			}
		}
	}
	virtual void DrawFrame() override
	{
		pipeline.Clear();

		pipeline.DrawTexture(player.pos, player.tex_pos, player.tex);

		pipeline.DrawTexture(missile.pos, missile.tex_pos, missile.tex);

		pipeline.DrawTexture(goal.pos, goal.tex_pos, goal.tex);

		for (int i = 0; i < walls.size(); i++)
		{
			pipeline.DrawColor(walls[i].pos, walls[i].dim, walls[i].c);
		}

		for (int i = 0; i < olofs.size(); i++)
		{
			pipeline.DrawTexture(olofs[i].pos, olofs[i].tex_pos, olofs[i].tex);
		}

		pipeline.Present();
	}
	virtual void InitializeScene() override
	{
		player = Player{ "player_pic", V2i{32,32}, V2d{750.0,350.0}, V2i{0,0},100.0, 5 };

		olofs.clear();
		walls.clear();

		walls.push_back(Wall{ V2d{100,100}, V2d{660,20}, Red });
		walls.push_back(Wall{ V2d{100,120}, V2d{20,400}, Red });
		walls.push_back(Wall{ V2d{0,0}, V2d{20,20}, Red });
		walls.push_back(Wall{ V2d{100,420}, V2d{700,20}, Red });
		walls.push_back(Wall{ V2d{250,300}, V2d{550,20}, Red });
		walls.push_back(Wall{ V2d{640,40}, V2d{20,100}, Red });

		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(250.0, 350.0), V2d(50.0, 50.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(400.0, 400.0), V2d(50.0, -50.0), Olof::State::alive });

		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(300.0, 250.0), V2d(100.0, 0.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(400.0, 200.0), V2d(-100.0, 0.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(500.0, 150.0), V2d(-50.0, 0.0), Olof::State::alive });

		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(50.0, 50.0), V2d(-100.0, 100.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(0.0, 250.0), V2d(-100.0, 100.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(50.0, 450.0), V2d(-50.0, 50.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(400.0, 50.0), V2d(-50.0, 50.0), Olof::State::alive });
		olofs.push_back(Olof{ "Olof", V2i{32,32}, "f1", V2d(500.0, 550.0), V2d(-50.0, 50.0), Olof::State::alive });
	}
private:
	std::vector<Olof> olofs;
	std::vector<Wall> walls;
	Player player{ "player_pic", V2i{32,32}, V2d{750.0,350.0}, V2i{0,0},100.0, 5 };
	Missile missile;
	Goal goal{ V2d{700.0,500.0}};
};