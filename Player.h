#pragma once

#include "BaseGeometry.h"
#include "Wall.h"
#include "Texture.h"
#include "Olof.h"
#include "Goal.h"

class Player
{
public:
	enum State
	{
		alive,
		dying,
		finished
	};
public:
	Player(std::string texture_name, V2i in_pic_dim, V2d in_pos, V2i in_tex_pos, double in_speed,
		int in_hp)
		:
		pos(in_pos),
		tex(texture_name, in_pic_dim),
		speed(in_speed),
		tex_pos(in_tex_pos),
		hp(in_hp)
	{
		dim.x = (double)in_pic_dim.x;
		dim.y = (double)in_pic_dim.y;
	}
	void ScreenCollision()
	{
		if (pos.x < 0.0)
		{
			pos.x = 0.0;
		}
		if (pos.x + dim.x > 799.0)
		{
			pos.x = 799.0 - dim.x;
		}
		if (pos.y < 0.0)
		{
			pos.y = 0.0;
		}
		if (pos.y + dim.y > 599.0)
		{
			pos.y = 599.0 - dim.y;
		}
	}
	void WallCollision(Wall& w)
	{
		// left
		if (pos.x < w.pos.x && pos.x + dim.x > w.pos.x)
		{
			// top left
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				double x_diff = pos.x + dim.x - w.pos.x;
				double y_diff = pos.y + dim.y - w.pos.y;
				if (x_diff >= y_diff)
				{
					pos.y = w.pos.y - dim.y;
				}
				else
				{
					pos.x = w.pos.x - dim.x;
				}
			}
			// mid left
			else if (pos.y >= w.pos.y && pos.y + dim.y <= w.pos.y + w.dim.y)
			{
				pos.x = w.pos.x - dim.x;
			}
			// bottom left
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				double x_diff = pos.x + dim.x - w.pos.x;
				double y_diff = w.pos.y + w.dim.y - pos.y;
				if (x_diff >= y_diff)
				{
					pos.y = w.pos.y + w.dim.y;
				}
				else
				{
					pos.x = w.pos.x - dim.x;
				}
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				pos.x = w.pos.x - dim.x;
			}
		}
		// right
		else if (pos.x < w.pos.x + w.dim.x && pos.x + dim.x > w.pos.x + w.dim.x)
		{
			// top right
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				double x_diff = w.pos.x + w.dim.x - pos.x;
				double y_diff = pos.y + dim.y - w.pos.y;
				if (x_diff >= y_diff)
				{
					pos.y = w.pos.y - dim.y;
				}
				else
				{
					pos.x = w.pos.x + w.dim.x;
				}
			}
			// mid right
			else if (pos.y >= w.pos.y && pos.y + dim.y <= w.pos.y + w.dim.y)
			{
				pos.x = w.pos.x + w.dim.x;
			}
			// bottom right
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				double x_diff = w.pos.x + w.dim.x - pos.x;
				double y_diff = w.pos.y + w.dim.y - pos.y;
				if (x_diff >= y_diff)
				{
					pos.y = w.pos.y + w.dim.y;
				}
				else
				{
					pos.x = w.pos.x + w.dim.x;
				}
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				pos.x = w.pos.x + w.dim.x;
			}
		}
		// mid, argument engulfs
		if (pos.x >= w.pos.x && pos.x + dim.x <= w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				pos.y = w.pos.y - dim.y;
			}
			// bottom mid
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				pos.y = w.pos.y + w.dim.y;
			}
		}
		// mid, caller engulfs
		else if (pos.x >= w.pos.x && pos.x + dim.x <= w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				pos.y = w.pos.y - dim.y;
			}
			// bottom mid
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				pos.y = w.pos.y + w.dim.y;
			}
		}
	}
	void EnemyCollision(Olof& w)
	{
		// left
		if (pos.x < w.pos.x && pos.x + dim.x > w.pos.x)
		{
			// top left
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = dying;
			}
			// mid left
			else if (pos.y >= w.pos.y && pos.y + dim.y <= w.pos.y + w.dim.y)
			{
				state = dying;
			}
			// bottom left
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = dying;
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = dying;
			}
		}
		// right
		else if (pos.x < w.pos.x + w.dim.x && pos.x + dim.x > w.pos.x + w.dim.x)
		{
			// top right
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = dying;
			}
			// mid right
			else if (pos.y >= w.pos.y && pos.y + dim.y <= w.pos.y + w.dim.y)
			{
				state = dying;
			}
			// bottom right
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = dying;
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = dying;
			}
		}
		// mid, argument engulfs
		if (pos.x >= w.pos.x && pos.x + dim.x <= w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = dying;
			}
			// bottom mid
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = dying;
			}
		}
		// mid, caller engulfs
		else if (pos.x >= w.pos.x && pos.x + dim.x <= w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = dying;
			}
			// bottom mid
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = dying;
			}
		}
	}
	void GoalCollision(Goal& w, int &scene)
	{
		// left
		if (pos.x < w.pos.x && pos.x + dim.x > w.pos.x)
		{
			// top left
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = finished;
			}
			// mid left
			else if (pos.y >= w.pos.y && pos.y + dim.y <= w.pos.y + w.dim.y)
			{
				state = finished;;
			}
			// bottom left
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = finished;;
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = finished;;
			}
		}
		// right
		else if (pos.x < w.pos.x + w.dim.x && pos.x + dim.x > w.pos.x + w.dim.x)
		{
			// top right
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = finished;;
			}
			// mid right
			else if (pos.y >= w.pos.y && pos.y + dim.y <= w.pos.y + w.dim.y)
			{
				state = finished;;
			}
			// bottom right
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = finished;;
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = finished;;
			}
		}
		// mid, argument engulfs
		if (pos.x >= w.pos.x && pos.x + dim.x <= w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = finished;;
			}
			// bottom mid
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = finished;;
			}
		}
		// mid, caller engulfs
		else if (pos.x >= w.pos.x && pos.x + dim.x <= w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = finished;;
			}
			// bottom mid
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = finished;;
			}
		}
	}
	void Dying(double& dt, int& scene)
	{
		if (timer == 0.0)
			namnam.Play();
		timer += dt;
		if (timer > 0.0 && timer <= 1.0)
			tex_pos = V2i{ 32,0 };
		if (timer > 1.0 && timer < 2.0)
		{
			tex_pos = V2i{ 96,0 };
		}
		if (timer > 2.0)
		{
			timer = 0.0;
			scene = 4;
		}
	}
	void Finishing(double& dt, int& scene)
	{
		if (timer == 0.0)
			hank.Play();
		timer += dt;
		if (timer > 0.0 && timer <= 2.0)
			tex_pos = V2i{ 64,0 };
		if (timer > 2.0)
		{
			timer = 0.0;
			scene++;
		}
	}
public:
	// position
	V2d pos;
	V2d dim;
	double speed;
	// state
	int hp;
	State state{ alive };
	double timer = 0.0;
	// graphics
	Texture tex;
	V2i tex_pos;
	// sounds
	Sound namnam{ "Namnam" };
	Sound hank{ "hank" };
};
