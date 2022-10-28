#include "Button.h"

Button::Button(float in_x, float in_y, float in_w, float in_h, const std::string& texture_file_path)
	:
	texture(texture_file_path)
{
	x = in_x;
	y = in_y;
	width = in_w;
	height = in_h;
}