#include "zArrayConverter.h"

float* zArrayConverter::convert_coordinates_to_vert_array(float arr[], float x, float y, float width, float height)
{
	// Bottom Left
	arr[0] = x;
	arr[1] = y;
	arr[2] = 0.0f;

	// Bottom Right
	arr[3] = 2.0f;
		// Top Right

		// Top Left
	return arr;
}

float* zArrayConverter::convert_coordinates_to_vert_tex_array(float arr[], float x, float y, float width, float height, float t_x, float t_y, float t_width, float t_height)
{
	// Bottom Left
	arr[0] = x;
	arr[1] = y;
	arr[2] = 0.0f;
	
	arr[3] = t_x;
	arr[4] = t_y;

	// Bottom Right
	arr[5] = x + width;
	arr[6] = y;
	arr[7] = 0.0f;

	arr[8] = t_x + t_width;
	arr[9] = t_y;

	// Top Right
	arr[10] = x + width;
	arr[11] = y + height;
	arr[12] = 0.0f;

	arr[13] = t_x + t_width;
	arr[14] = t_y + t_height;

	// Top Left
	arr[15] = x;
	arr[16] = y + height;
	arr[17] = 0.0f;

	arr[18] = t_x;
	arr[19] = t_y + t_height;

	return arr;
}