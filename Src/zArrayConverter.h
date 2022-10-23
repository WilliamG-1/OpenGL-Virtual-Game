#pragma once
class zArrayConverter
{
public:
	static float* convert_coordinates_to_vert_array(float arr[], float x, float y, float width, float height);
	static float* convert_coordinates_to_vert_tex_array(float arr[], float x, float y, float width, float height, float t_x, float t_y, float t_width, float t_height);
	static void convert_coordinates_to_vert_tex_array_reference(float (&arr)[20], float x, float y, float width, float height, float t_x, float t_y, float t_width, float t_height);
	static void shift_texture_coordinates(float(&arr)[20], float x_offset, float y_offset);
private:

};
