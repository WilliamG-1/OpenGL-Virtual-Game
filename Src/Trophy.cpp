#include "Trophy.h"

Trophy::Trophy(float in_x, float in_y, float in_w, float in_h)
	:
	Entity(in_x, in_y, in_w, in_h)
{
	xVel = 0.0f;
	yVel = 1.0f;
}

void Trophy::move(float dt)
{
	if (y > initialY + maxDisplacement || y < initialY)
		yVel *= -1;		// Invert move speed if out of distance

	y += yVel * dt;
}

void Trophy::collection_move(float dt)
{
	yVel = 2.0f;
	y += yVel * dt;
	if (y > initialY + 5)
		yVel = 0;
}