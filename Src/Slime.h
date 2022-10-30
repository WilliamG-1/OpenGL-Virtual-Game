#pragma once
#include "Entity.h"
#include "Texture.h"
class Slime : public Entity
{
public:
	Slime(float in_x, float in_y, float in_w, float in_h, bool start_from_right = false);

	void move(float dt);

	float& get_current_walk_frame() { return walkFrame; }
private:
	float walkFrame = 0.0f;
	float maxDisplacement = 500.0f;
	float initialX;
};