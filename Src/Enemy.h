#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(float in_x, float in_y, float width, float height);
private:
	float velocity;
};
