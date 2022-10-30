#pragma once
#include <string>
class Button
{
public:
	Button(float in_x, float in_y, float in_w, float in_h);
	float getX() const { return x; }
	float getY() const { return y; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }
private:

	float x;
	float y;
	float width;
	float height;
};
