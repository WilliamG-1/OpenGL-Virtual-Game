#include "Player.h"
#include <math.h>
Player::Player(float in_x, float in_y, float in_width, float in_height)
	:
	Entity(in_x, in_y, in_width, in_height),
	velocity(30.0f, 0.0f)
{
	this->xVel = velocity.x;
	this->yVel = velocity.y;
}

float Player::getVx() const
{
	return velocity.x;
}

float Player::getVy() const
{
	return velocity.y;
}

float Player::getGravity() const
{
	return gravity;
}

void Player::setVx(float in_x)
{
	velocity.x = in_x;
}

void Player::setVy(float in_y)
{
	velocity.y = in_y;
}

void Player::applyGravity(float dt)
{
	this->velocity.y = this->velocity.y + (this->gravity * dt);
	if (this->velocity.y < this->gravity)
		velocity.y = gravity;
	this->yVel = this->velocity.y;
}

void Player::jump(float dt)
{
	this->velocity.y = 180.0f;
}
