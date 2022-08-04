#pragma once
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



enum class ArrayType {
	VERTEX = 0, ELEMENT
};

class Game
{
public:
	Game();
	~Game();
	void run();
	void processInput();

	
private:
	template <typename T>
	void copyArrToStruct(struct Arrays& A, T data[], unsigned int size, ArrayType type);
		
	Window window;
	Arrays wrapper;
	VertexArray VAO;
	//Arrays wrapper2;
	//VertexArray VAO2;

	Texture texture;
	 
	Shader shader;
	//Shader shader2;
	Renderer renderer;
	

	
	float vertices[20] =
	{
		// Vertex Coords		Tex Coords
		-0.5f, -0.5f,  0.0f,		0.0f, 0.0f, // Bottom Left  (0)
		 0.5f, -0.5f,  0.0f,		1.0f, 0.0f, // Bottom Right (1)
		 0.5f,  0.5f,  0.0f,		1.0f, 1.0f,	// Top Right    (2)
		-0.5f,  0.5f,  0.0f,		0.0f, 1.0f  // Top Left		(3)
	};
	unsigned int indices[6] =
	{
		0, 2, 3,
		0, 1, 2
	};
	
	
	void composeFrame();
	bool gameRunning = true;
	bool drawTriangle = true;
	float leftRightMove = 0.0f;
	float scaleRate = 1.0f;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	
};

