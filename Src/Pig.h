#pragma once
#include "Entity.h"

class Pig : public Entity
{
public:
	Pig(float in_x, float in_y, float width, float height);


	void move(float dt);
	void enrage();

	bool is_enraged();
	bool spotted_player(Entity& player);
private:
	float m_maxDisplacement = 400.0f;
	float m_velocity;
	float m_initialX = x;
	bool enraged;
};
