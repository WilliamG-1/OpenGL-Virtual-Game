#include "Tile.h"

Tile::Tile()
{
	x = 0.0f;
	y = 0.0f;
	width = 64.0f;
	height = 64.0f;
}

Tile::Tile(float in_x, float in_y, float in_width, float in_height)
{
	x = in_x;
	y = in_y;
	width = in_width;
	height = in_height;
}

float Tile::getX() const
{
	return this->x;
}

float Tile::getY() const
{
	return this->y;
}

float Tile::getWidth() const
{
	return this->width;
}

float Tile::getHeight() const
{
	return this->height;
}

bool Tile::is_in_frame() const
{
	return ((x > 0) && (x + width < 1024) && (y > 0) && (y + height < 768));
}

void Tile::setX(float dx)
{
	this->x = dx;
}

void Tile::setY(float dy)
{
	this->y = dy;
}
