#pragma once
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Player.h"
#include <memory>
#include "zArrayConverter.h"
#include "Tile.h"
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

	Player player;
	VertexArray VAO;
	VertexArray VAOPlayer;
	Level level;
	Tile backgroundTitle;
	Tile grassTile;
	Texture texture;
	Texture texture2;
	Texture playerTex;
	//std::vector<Texture> idleAnimation;
	std::vector<std::unique_ptr<Texture>> frames;

	float currentFrame = 0;

	Shader shader;
	//Shader shader2;
	Renderer renderer;
	
	// Tile Vertices
	float vertices[20] = {
		// Vertex Coords			Texture Coords
		000.0f, 704.0f, 0.0f,		0.0f, 0.0f,     // Bottom Left  (0)
		064.0f, 704.0f, 0.0f,		1.0f, 0.0f,     // Bottom Right (1)
		064.0f, 768.0f, 0.0f,		1.0f, 1.0f,     // Top Right    (2)
		000.0f, 768.0f, 0.0f,		0.0f, 1.0f		// Top Left     (3)

	};

	// Player Vertices
	float vertices2[20] = {
		// Vertex Coords		Texture Coords
		00.0f, 00.0f, 0.0f,		0.125f, 0.000f,	 // Bottom Left  (0)
		64.0f, 00.0f, 0.0f,		0.875f, 0.000f,	 // Bottom Right (1)
		64.0f, 64.0f, 0.0f,		0.875f, 0.825f,	 // Top Right    (2)
		00.0f, 64.0f, 0.0f,		0.125f, 0.825f	 // Top Left     (3)
	};
	
	void composeFrame();
	bool gameRunning = true;
	bool drawTriangle = true;
	float leftRightMove = 0.0f;
	float scaleRate = 1.0f;
	float move = 0;

	glm::mat4 MVP_Scene;
	glm::mat4 proj;
	glm::mat4 model;
	glm::mat4 view;
	
	glm::mat4 MVP_Player;
	glm::mat4 playerModel;
	glm::mat4 playerView;

	std::vector<char> board;
};

