#pragma once
class TextureOffsetConverter
{
public:
	static void calculate_initial_coordinates();
	static void calculate_texture_offset(unsigned int image_width, unsigned int image_height, unsigned int left_distance, unsigned int sprite_width, unsigned int down_distance, unsigned int sprite_height);
private:

};
