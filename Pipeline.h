#pragma once

#include "Graphics.h"
#include "Matrix.h"
#include "BaseGeometry.h"
#include "Font.h"
#include "Texture.h"

class Pipeline
{
public:
	Pipeline(Graphics& in_gfx)
		:
		gfx(in_gfx)
	{}
	void Clear()
	{
		gfx.Clear();
	}

	// color in big room
	/*
	void Draw2d(const V2d& pos, const V2d& dim, const Color& c, const V2d& ScreenPos, const V2d& ScreenDim)
	{
		for (int i = 0; i < (int)dim.x; i++)
		{
			for (int j = 0; j < (int)dim.y; j++)
			{
				int x = (int)(pos.x + 0.5) + i;
				int y = (int)(pos.y + 0.5) + j;
				if (x >= (int)ScreenPos.x && x < (int)ScreenPos.x + (int)ScreenDim.x 
					&& y >= (int)ScreenPos.y && y < (int)ScreenPos.y + (int)ScreenDim.y)
				{
					if (c.alpha == 255u)
					{
						gfx.SetPixel(x - (int)ScreenPos.x, y - (int)ScreenPos.y,
							c.red, c.green, c.blue, c.alpha);
					}
					else
					{
						Color oc = gfx.GetPixel(x, y);
						double bf = c.alpha / 255u;
						assert(bf >= 0.0 && bf <= 1.0);
						char red = bf * c.red + (1.0 - bf) * oc.red;
						char green = bf * c.green + (1.0 - bf) * oc.green;
						char blue = bf * c.blue + (1.0 - bf) * oc.blue;

						gfx.SetPixel(x - (int)ScreenPos.x, y - (int)ScreenPos.y,
							red, green, blue, 255u);
					}
				}
			}
		}
	}
	// image in big room
	void Draw2d(const V2d& pos, const V2d& dim, const std::vector<Color>& image, const V2d& ScreenPos, const V2d& ScreenDim)
	{
		for (int i = 0; i < (int)dim.x; i++)
		{
			for (int j = 0; j < (int)dim.y; j++)
			{
				int x = (int)(pos.x + 0.5) + i;
				int y = (int)(pos.y + 0.5) + j;
				if (x >= (int)ScreenPos.x && x < (int)ScreenPos.x + (int)ScreenDim.x
					&& y >= (int)ScreenPos.y && y < (int)ScreenPos.y + (int)ScreenDim.y)
				{
					
					if (!(image[j * (int)dim.x + i].red == 255u
						&& image[j * (int)dim.x + i].green == 255u
						&& image[j * (int)dim.x + i].blue == 255u))
					
					const Color c = image[j * (int)dim.x + i];
					if ( c!=White)
					{
						
						if (c.alpha == 255u)
						{
							gfx.SetPixel(x - (int)ScreenPos.x, y - (int)ScreenPos.y,
								c.red, c.green, c.blue, c.alpha);
						}
						else
						
						{
							Color oc = gfx.GetPixel(x, y);
							double bf = c.alpha / 255u;
							assert(bf >= 0.0 && bf <= 1.0);
							char red = bf * c.red + (1.0 - bf) * oc.red;
							char green = bf * c.green + (1.0 - bf) * oc.green;
							char blue = bf * c.blue + (1.0 - bf) * oc.blue;

							gfx.SetPixel(x - (int)ScreenPos.x, y - (int)ScreenPos.y,
								red, green, blue, 255u);
						}
					}
				}
			}
		}
	}
	*/
	// color in small room
	void DrawColor(const V2d& pos, const V2d& dim, const Color& c)
	{
		for (int i = 0; i < (int)dim.x; i++)
		{
			for (int j = 0; j < (int)dim.y; j++)
			{
				int x = (int)(pos.x + 0.5) + i;
				int y = (int)(pos.y + 0.5) + j;
				if (x >= 0 && x < 800 && y >= 0 && y < 600)
				{
					gfx.SetPixel((int)(pos.x + 0.5) + i, (int)(pos.y + 0.5) + j,
						c.red, c.green, c.blue, c.alpha);
				}
			}
		}
	}
	// image in small room
	void Draw2d(const V2d& pos, const V2d& dim, const V2d& tex_pos, const std::vector<Color>& image)
	{
		for (int i = 0; i < (int)dim.x; i++)
		{
			for (int j = 0; j < (int)dim.y; j++)
			{
				int x = (int)(pos.x + 0.5) + i;
				int y = (int)(pos.y + 0.5) + j;
				if (x >= 0 && x < 800 && y >= 0 && y < 600)
				{
					/*
					if (!(image[j * (int)dim.x + i].red == 255u
						&& image[j * (int)dim.x + i].green == 255u
						&& image[j * (int)dim.x + i].blue == 255u))
					*/
					{
						gfx.SetPixel(x, y,
							image[j * (int)dim.x + i].red, image[j * (int)dim.x + i].green,
							image[j * (int)dim.x + i].blue, image[j * (int)dim.x + i].alpha);
					}
				}
			}
		}
	}

	void DrawTexture(const V2d pos, const V2i tex_pos, const Texture& texture)
	{
		for (int j = 0; j < texture.pic_dim.y; j++)
		{
			for (int i = 0; i < texture.pic_dim.x; i++)
			{
				// get screen coordinates
				int x = (int)(pos.x + 0.5) + i;
				int y = (int)(pos.y + 0.5) + j;

				if (x >= 0 && x < 800 && y >= 0 && y < 600)
				{
					// get position in texture vector (get the color)
					int vec_pos = tex_pos.y * texture.dim.x
						+ j * texture.dim.x + tex_pos.x + i;

					if (texture.tex[vec_pos] != White)
					{
						gfx.SetPixel(x, y,
							texture.tex[vec_pos].red,
							texture.tex[vec_pos].green,
							texture.tex[vec_pos].blue,
							texture.tex[vec_pos].alpha);
					}
				}
			}
		}
	}

	void DrawText_(const V2i pos, const Font& font, const std::string& text, const Color text_color)
	{
		V2i CurPos = pos;
		for (char c : text)
		{
			if (c >= font.first_char && c <= font.last_char)
			{
				if (c == '/')
				{
					CurPos.x = pos.x;
					CurPos.y += 20;
				}
				else
				{
					for (int y = 0; y < font.char_dim.y; y++)
					{
						for (int x = 0; x < font.char_dim.x; x++)
						{
							// get position in font
							char a = '`';
							int font_pos = 0;
							int step = (c - ' ') / 32;
							assert(step == 0 || step == 1 || step == 2);
							if (step == 0)
								font_pos = (c - ' ') * 12 + x + y * (32 * 12);
							if (step == 1)
								font_pos = (c - '@') * 12 + x + y * (32 * 12) + step * 32 * 20 * 12;
							if (step == 2)
								font_pos = (c - '`') * 12 + x + y * (32 * 12) + step * 32 * 20 * 12;
							// get color
							Color color = Color(font.font[font_pos]);
							/*
							if (color != White && color != Black)
								color = Blue;
								*/
							if (color != White)
							{
								/*
								if (color == Black)
									color = text_color;
									*/
								color = text_color;
								gfx.SetPixel(CurPos.x + x, CurPos.y + y, color.red, color.green, color.blue, 0u);
							}
						}
					}
					CurPos.x += font.char_dim.x;
				}

			}
		}
	}
	void Draw3d()
	{

	}
	void Present()
	{
		gfx.Present();
	}
public:
	Graphics& gfx;
};


/*

#include "Pipeline.h"

void Pipeline::Draw(IndexedTriangleList& trilist)
{
	ProcessVerteces(trilist);
}

void Pipeline::ProcessVerteces(IndexedTriangleList& trilist)
{
	// vertex shader stuff
	AssembleTriangles(trilist.verteces, trilist.indices);
}

void Pipeline::AssembleTriangles(std::vector<Vertex> verteces, std::vector<int> indices)
{
	// get eye position
	Vertex eyepos = Vertex(0.0f, 0.0f, 0.0f);

	// assemble triangles, do backface culling, and call processtriangle
	for (int i = 0; i < indices.size(); std::advance(i, 3))
	{
		// build the triangle
		Vertex& v1 = verteces[indices[i]];
		Vertex& v2 = verteces[indices[i + 1]];
		Vertex& v3 = verteces[indices[i + 2]];

		// get cross product
		Vertex cp1 = v2 - v1;
		Vertex cp2 = v3 - v1;
		Vertex cp = CrossProduct(cp1,cp2);

		// cull backfacing triangles and process the remainder
		if (cp * (v1 - eyepos) <= 0)
		{
			ProcessTriangle(v1, v2, v3);
		}
	}
}

void Pipeline::ProcessTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	// do clipping

	// get z-inverses
	float v1_inv = 1 / v1.GetZ(); float v2_inv = 1 / v2.GetZ(); float v3_inv = 1 / v3.GetZ();

	// do world space to screen space transformation
	v1.SetX((v1.GetX() + 1.0f) * gfx.GetWidth() * 0.5f);
	v1.SetY((v1.GetY() + 1.0f) * gfx.GetHeight() * 0.5f);
	v2.SetX((v2.GetX() + 1.0f) * gfx.GetWidth() * 0.5f);
	v2.SetY((v2.GetY() + 1.0f) * gfx.GetHeight() * 0.5f);
	v3.SetX((v3.GetX() + 1.0f) * gfx.GetWidth() * 0.5f);
	v3.SetY((v3.GetY() + 1.0f) * gfx.GetHeight() * 0.5f);

	// sort verteces by y
	Vertex* pv1 = &v1; 	Vertex* pv2 = &v2; 	Vertex* pv3 = &v3;
	if (pv2->GetY() < pv1->GetY()) std::swap(pv2, pv1);
	if (pv3->GetY() < pv2->GetY()) std::swap(pv3, pv2);
	if (pv2->GetY() < pv1->GetY()) std::swap(pv2, pv1);

	// flat top triangle
	if (pv1->GetY() == pv2->GetY())
	{
		if (pv2->GetX() < pv1->GetY()) std::swap(pv1, pv2); // we want the order top left, top right, bottom
		DrawFlatTopTriangle(*pv1, *pv2, *pv3);
	}

	// flat bottom triangle
	if (pv2->GetY() == pv3->GetY())
	{
		if (pv2->GetX() < pv3->GetY()) std::swap(pv2, pv3); // we want the order top, bottom right, bottom left
		DrawFlatBottomTriangle(*pv1, *pv2, *pv3);
	}

	// general triangle
	else
	{
		// find the splitting vertex interpolant
		float alpha = (pv1->GetY() - pv2->GetY()) / (pv1->GetY() - pv3->GetY());
		Vertex vi = interpolate(*pv1, *pv3, alpha);

		// major left
		if (pv2->GetX() > vi.GetX())
		{
			DrawFlatTopTriangle(vi, *pv2, *pv3);
			DrawFlatBottomTriangle(*pv1, *pv2, vi);
		}

		// major right
		else
		{
			DrawFlatTopTriangle(*pv2, vi, *pv3);
			DrawFlatBottomTriangle(*pv1, vi, *pv2);
		}
	}
}

void Pipeline::DrawFlatTopTriangle(Vertex v1, Vertex v2, Vertex v3)
{

}

void Pipeline::DrawFlatBottomTriangle(Vertex v1, Vertex v2, Vertex v3)
{

}



*/