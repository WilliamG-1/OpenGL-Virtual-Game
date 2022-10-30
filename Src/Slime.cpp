#include "Slime.h"


Slime::Slime(float in_x, float in_y, float in_w, float in_h, bool start_from_right)
	:
	Entity(in_x, in_y, in_w, in_h)	
{
	xVel = 10.0f;
	initialX = x;
	if (start_from_right)
		x += maxDisplacement;
}

void Slime::move(float dt)
{
	if (x >= initialX + maxDisplacement || x <= initialX)
		xVel *= -1;	// Change velocity at either ends of movement border
	x += xVel * dt;
}