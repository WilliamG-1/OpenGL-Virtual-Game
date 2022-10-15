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

enum class CanMove
{
	RIGHT = 0,
	LEFT = 1,
	UP = 2,
	DOWN = 3
};
class Entity
{
public:
	Entity(float in_x, float in_y, float in_width, float in_height);
	void moveX(float dt);
	void moveY(float dt);

	bool is_moving_left() const;
	bool is_moving_right() const;
	bool is_jumping() const;
	bool is_falling() const;
	bool is_moving();

	bool can_move_right() const;
	bool can_move_left() const;
	bool can_move_up() const;
	bool can_move_down() const;

	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;

	void setX(float x);
	void setY(float y);

	void set_moving_right_state(bool state);
	void set_moving_left_state(bool state);
	void set_moving_up_state(bool state);


	void set_can_move_left(bool state);
	void set_can_move_right(bool state);
	void set_can_move_down(bool state);
	void set_can_jump(bool state);
	
protected:
	MoveState move_state;
	std::vector<bool> movement = { 0, 0, 0, 0, 0 };
	std::vector<bool> canMove = { 1, 1, 1, 1 };
	float x;
	float y;
	float width;
	float height;
	float yVel = 0.0f;
	float xVel = 0.0f;

};