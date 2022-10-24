#pragma once
#include "Entity.h"
#include "Fruit.h"

class Pig : public Entity
{
public:
	Pig(float in_x, float in_y, float width, float height, float max_displacement = 400.0f);


	void move(float dt);
	void stop();

	void check_fruit_existance(Fruit& fruit);
	void enrage();

	bool is_enraged();
	bool spotted_player(Entity& player);

	float& get_walk_frame() { return walkFrame; }
	float& get_run_frame() { return runFrame; }
private:
	float walkFrame = 0.0f;
	float runFrame = 0.0f;
	float m_maxDisplacement = 400.0f;
	float m_velocity;
	float m_initialX = x;
	bool enraged;
};
