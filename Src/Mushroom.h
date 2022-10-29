#pragma once
#include "Entity.h"
class Mushroom : public Entity
{
public:
	Mushroom(float in_x, float in_y, float in_w, float in_h);

private:
	float walk_frame = 0.0f;


};
