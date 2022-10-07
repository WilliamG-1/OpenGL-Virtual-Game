#pragma once
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"


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
	Level level;
	Texture texture;
	Texture texture2;
	 
	Shader shader;
	//Shader shader2;
	Renderer renderer;
	

	
	//float vertices[40] =
	//{
	//	// Vertex Coords		Tex Coords
	//	 00.0f,  00.0f,  00.0f,		0.000f, 0.375f, // Bottom Left  (0)
	//	 32.0f,  00.0f,  00.0f,		0.125f, 0.375f, // Bottom Right (1)
	//	 32.0f,  32.0f,  00.0f,		0.125f, 0.500f,	// Top Right    (2)
	//	 00.0f,  32.0f,  00.0f,		0.000f, 0.500f, // Top Left		(3)
	//
	//	 000.0f, 512.0f, 0.0f,		0.000f, 0.500f, // Bottom Left Grass  (4)
	//	 128.0f, 512.0f, 0.0f,		0.500f, 0.500f, // Bottom Right Grass (5)
	//	 128.0f, 640.0f, 0.0f,		0.500f, 1.000f, // Top Right Grass    (6)
	//	 000.0f, 640.0f, 0.0f,      0.000f, 1.000f  // Top Left Grasss    (7)
	//
	//
	//};
	//float vertices[20] =
	//{
	//	// Vertex Coords		Tex Coords
	//	 000.0f,  000.0f,  000.0f,		0.0f, 0.0f, // Bottom Left  (0)
	//	 0.5f,  000.0f,  000.0f,		1.0f, 0.0f, // Bottom Right (1)
	//	 0.5f,  0.5f,  000.0f,		1.0f, 1.0f,	// Top Right    (2)
	//	 000.0f,  0.5f,  000.0f,		0.0f, 1.0f  // Top Left		(3)
	//};
	//unsigned int indices[12] =
	//{
	//	0, 2, 3,
	//	0, 1, 2,
	//
	//	4, 6, 7,
	//	4, 5, 6
	//};
	
	
	void composeFrame();
	bool gameRunning = true;
	bool drawTriangle = true;
	float leftRightMove = 0.0f;
	float scaleRate = 1.0f;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	std::vector<char> board;
	
};

