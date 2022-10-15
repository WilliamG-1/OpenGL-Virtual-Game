#pragma once
class Tile
{
public:
	Tile();
	Tile(float in_x, float in_y, float in_width, float in_height);
	float getX() const;
	float getY() const;
	float get_starting_x() const;
	float get_starting_y() const;
	float getWidth() const;
	float getHeight() const;
	bool is_in_frame() const;

	void setX(float dx);
	void setY(float dy);
private:
	float starting_x;
	float starting_y;
	float x;
	float y;
	float width;
	float height;
};
