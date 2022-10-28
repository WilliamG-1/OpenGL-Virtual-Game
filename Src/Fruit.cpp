#include "Fruit.h"
#include <iostream>
Fruit::Fruit(float in_x, float in_y, float in_w, float in_h)
{
	x = in_x;
	y = in_y;
	width = in_w;
	height = in_h;
}

void Fruit::init(float in_x, float in_y, float in_w, float in_h)
{
	x = in_x;
	y = in_y;
	width = in_w;
	height = in_h;
}

void Fruit::collect()
{
	collected = true;
}

bool Fruit::is_collected() const
{
	return collected;
}

Fruit::~Fruit()
{
	std::cout << "Destroyed Fruit" << std::endl;
}