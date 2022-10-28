#pragma once
#include "Texture.h"
#include "Entity.h"
#include <string>
#include <glm/glm.hpp>


class Player: public Entity
{
public:
	Player(float in_x, float in_y, float in_width, float in_height);
	float getVx() const;
	float getVy() const;
	float getGravity() const;

	void setVx(float in_x);
	void setVy(float in_y);

	void applyGravity(float dt);
	void jump(float dt);

private:
	glm::vec2 velocity;
	float gravity = -100.0f;
};

