#pragma once

class Fruit
{
public:
	Fruit(float in_x, float in_y, float in_w, float in_h);
	~Fruit();

	void init(float in_x, float in_y, float in_w, float in_h);
	void collect();

	bool is_collected() const;

	float getX() const { return x; }
	float getY() const { return y; }
	float getWidth() const { return width; }
	float getHeight() const { return height; }
	float& get_frame() { return frame; }
private:
	bool collected = false;
	float x;
	float y;
	float width;
	float height;
	float frame = 0.0f;
};