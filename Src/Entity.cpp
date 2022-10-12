#include "Entity.h"

Entity::Entity(float in_x, float in_y, float in_width, float in_height)
{
	x = in_x;
	y = in_y;
	width = in_width;
	height = in_height;
	speed = 1.0f;
}

void Entity::moveX(float dx)
{
	if (dx > 0)
	{
		movement[static_cast<int>(MoveState::MOVING_RIGHT)] = true;
		movement[static_cast<int>(MoveState::MOVING_LEFT)] = false;
	}
	if (dx < 0)
	{
		movement[static_cast<int>(MoveState::MOVING_RIGHT)] = 0; // Not Moving Right
		movement[static_cast<int>(MoveState::MOVING_LEFT)] = 1;  // Moving Left
	}

	if (dx == 0)
	{
		movement[static_cast<int>(MoveState::MOVING_RIGHT)] = 0; // Not Moving Right
		movement[static_cast<int>(MoveState::MOVING_LEFT)] = 0;  // Moving Left
	}
	x += dx * speed;
}

void Entity::moveY(float dy)
{
	if (dy > 0)
	{
		movement[static_cast<int>(MoveState::JUMPING)] = true;
		movement[static_cast<int>(MoveState::FALLING)] = false;
	}
	if (dy < 0)
	{
		movement[static_cast<int>(MoveState::JUMPING)] = false;
		movement[static_cast<int>(MoveState::FALLING)] = true;
	}

	if (dy == 0)
	{
		movement[static_cast<int>(MoveState::JUMPING)] = false;
		movement[static_cast<int>(MoveState::FALLING)] = false;
	}
	y += dy;
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
	for (int i = 1; i < 5; i++)
	{
		if (movement[i])
			return true;
	}
	return false;
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
