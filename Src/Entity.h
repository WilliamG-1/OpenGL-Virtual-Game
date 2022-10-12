#pragma once
#include <vector>
enum class MoveState
{
	STANDING_STILL = 0,
	MOVING_RIGHT = 1,
	MOVING_LEFT = 2,
	JUMPING = 3,
	FALLING = 4
};

class Entity
{
public:
	Entity(float in_x, float in_y, float in_width, float in_height);
	void moveX(float dx);
	void moveY(float dy);

	bool is_moving_left() const;
	bool is_moving_right() const;
	bool is_jumping() const;
	bool is_falling() const;
	bool is_moving();

	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
private:
	MoveState move_state;
	std::vector<bool> movement = { 0, 0, 0, 0, 0 };
	float x;
	float y;
	float width;
	float height;
	float speed;

};