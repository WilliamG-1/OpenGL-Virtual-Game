#pragma once
#include "VertexArray.h"
#include "Shader.h"
class Renderer
{
public:
	Renderer();
	~Renderer();

	void draw(VertexArray& VAO, Shader& shader);
	

private:

};

