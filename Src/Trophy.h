#pragma once
#include "Entity.h"
class Trophy : public Entity
{
public:
	Trophy(float in_x, float in_y, float in_w, float in_h);

	void move(float dt);
	void collection_move(float dt);
	bool is_collected() const { return isCollected; }
	
	float get_initial_y() const { return initialY; }
private:
	bool isCollected;
	float maxDisplacement = 15.0f;
	float initialY = y;
};
