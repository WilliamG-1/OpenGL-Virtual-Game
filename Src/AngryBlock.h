#pragma once
#include "Entity.h"
class AngryBlock : public Entity
{
public:
	AngryBlock(float in_x, float in_y, float in_w, float in_h);
	AngryBlock(float in_x, float in_y, float in_w, float in_h, float in_downTime, float in_moveTime); // Constructor to specify move time and down time
	void update_timer(float dt);
	void moveY(float dt);

	bool is_moving() { return (xVel + yVel != 0.0f); }
	float& get_blink_frame() { return blinkFrame; }
	float get_move_timer() { return moveTimer; }
private:
	int direction = 1;	// Negative/Positive sign value
	float initialY = y; // Initial y placement of dude
	float max_displacement = 200.0f; // Maximum displacement thwomp dude can travel
	float moveTimer = 0.0f; // Timer to control movement
	float blinkFrame = 0.0f; // Timer for blinking frames
	float blinkTimer = 0.0f;
	bool can_blink = false;

	float downTime = 20.0f; // Time window where angry block will not move
	float moveTime = 14.0f; // TIme window where angry block will move
};
