#include "Entity.h"

Entity::Entity(float in_x, float in_y, float in_width, float in_height)
{
	x = in_x;
	y = in_y;
	width = in_width;
	height = in_height;
}

void Entity::moveX(float dt)
{
	if (xVel > 0)
	{
		movement[static_cast<int>(MoveState::MOVING_RIGHT)] = true;
		movement[static_cast<int>(MoveState::MOVING_LEFT)] = false;
	}
	else if(xVel < 0)
	{
		movement[static_cast<int>(MoveState::MOVING_RIGHT)] = 0; // Not Moving Right
		movement[static_cast<int>(MoveState::MOVING_LEFT)] = 1;  // Moving Left
	}

	this->x += xVel * dt;
}

void Entity::moveY(float dt)
{
	this->y += (this->yVel)*dt;
	if (this->yVel < 0)
	{
		movement[static_cast<int>(MoveState::FALLING)] = true;
	}
	else
		movement[static_cast<int>(MoveState::FALLING)] = false;
}

bool Entity::is_moving_left() const
{
	return movement[static_cast<int>(MoveState::MOVING_LEFT)];
}

bool Entity::is_moving_right() const
{
	return movement[static_cast<int>(MoveState::MOVING_RIGHT)];
}

bool Entity::is_jumping() const
{
	return movement[static_cast<int>(MoveState::JUMPING)];
}

bool Entity::is_falling() const
{
	return movement[static_cast<int>(MoveState::FALLING)];
}

bool Entity::is_moving()
{
	for (int i = 1; i < 4; i++)
	{
		if (movement[i])
			return true;
	}
	return false;
}

bool Entity::can_move_right() const
{
	return canMove[static_cast<int>(CanMove::RIGHT)];
}

bool Entity::can_move_left() const
{
	return canMove[static_cast<int>(CanMove::LEFT)];
}

bool Entity::can_move_up() const
{
	return canMove[static_cast<int>(CanMove::UP)];
}

bool Entity::can_move_down() const
{
	return canMove[static_cast<int>(CanMove::DOWN)];
}

float Entity::getX() const
{
	return x;
}

float Entity::getY() const
{
	return y;
}

float Entity::getWidth() const
{
	return width;
}

float Entity::getHeight() const
{
	return height;
}

void Entity::setX(float x)
{
	this->x = x;
}

void Entity::setY(float y)
{
	this->y = y;
}


void Entity::set_moving_right_state(bool state)
{
	movement[static_cast<int>(MoveState::MOVING_RIGHT)] = state;
}

void Entity::set_moving_left_state(bool state)
{
	movement[static_cast<int>(MoveState::MOVING_LEFT)] = state;  // Moving Left
}

void Entity::set_moving_up_state(bool state)
{
	movement[static_cast<int>(MoveState::JUMPING)] = state;
}

void Entity::set_can_move_left(bool state)
{
	canMove[static_cast<int>(CanMove::LEFT)] = state;
}

void Entity::set_can_move_right(bool state)
{
	canMove[static_cast<int>(CanMove::RIGHT)] = state;
}

void Entity::set_can_jump(bool state)
{
	canMove[static_cast<int>(CanMove::UP)] = state;
}

void Entity::set_can_move_down(bool state)
{
	canMove[static_cast<int>(CanMove::DOWN)] = state;
}
