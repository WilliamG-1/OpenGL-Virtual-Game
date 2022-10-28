#include "AngryBlock.h"

AngryBlock::AngryBlock(float in_x, float in_y, float in_w, float in_h)
	: Entity(in_x, in_y, in_w, in_h)
{
	xVel = 0.0f;
	yVel = 15.0f;
}

void AngryBlock::moveY(float dt)
{
	y += yVel * dt * (float)direction;
}

void AngryBlock::update_timer(float dt)
{
	// Movement 
	if (moveTimer >= 0 && moveTimer <= 15.0f) {		
		direction = 1;		// If time between this window, rock dude will move up (sign is positive)
	}
	else if (moveTimer >= 25.0f && moveTimer <= 40.0f)
	{
		direction = -1;		// If time is between this window, rock dude will move down (sign is negative)
	}
	else direction = 0;		// If time not within window, rock dude will stop 

	if (moveTimer >= 50.0f)					
	{
		moveTimer = 0.0f;	// Reset timer after reaching max time
	}
	moveTimer += dt;


	// Blinking Frames
	if ((int)blinkTimer % 22 == 0 || (int)blinkTimer % 49 == 0)
	{
		can_blink = true;	// At certain intervals, blink animation can begin
	}
	if (blinkFrame >= 5.9f)
	{
		blinkFrame = 0.0f;	// Reset to 0 when full blink sprite cycle completed
		can_blink = false;	// Once full blink cycle complete, blink animation will halt
	}
	if (can_blink)	
		blinkFrame += dt*2.5;	// Start blink cycle if blinking allowed 

	blinkTimer += dt;		// Add blink Timer by dt
	if (blinkTimer > 300)	
		blinkTimer = 0.0f;	// Reset blink time to 0
}