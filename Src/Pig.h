#pragma once
#include "Entity.h"

class Pig : public Entity
{
public:
	Pig(float in_x, float in_y, float width, float height);

private:
	int m_maxDisplacement;
	float m_velocity;
};
