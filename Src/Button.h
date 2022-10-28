#pragma once
#include "Texture.h"
#include <string>
class Button
{
public:
	Button(float in_x, float in_y, float in_w, float in_h, const std::string& tex_file_path);
	Texture& get_texture() { return texture; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }
private:
	Texture texture;
	float x;
	float y;
	float width;
	float height;
};
