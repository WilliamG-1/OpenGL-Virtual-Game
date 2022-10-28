#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
public:


private:
	glm::mat4 modelProjection;
	glm::mat4 projection;
	glm::mat4 view;
};
