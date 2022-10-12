#pragma once
class Tile
{
public:
	Tile();
	Tile(float in_x, float in_y, float in_width, float in_height);
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	bool is_in_frame() const;
private:
	float x;
	float y;
	float width;
	float height;
};
