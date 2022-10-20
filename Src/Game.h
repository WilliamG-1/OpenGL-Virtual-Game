#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Level.h"
#include "Player.h"
#include "zArrayConverter.h"
#include "Tile.h"

#include "Physics.h"

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
	float screenWidth = 1024.0f;
	float screenHeight = 768.0f;
	float moveSpeed = 40.0f;
	Window window;
	Arrays wrapper;

	glm::vec2 playerStartingCoords = { 125.0f, 500.0f };
	Player player;
	VertexArray VAO;
	VertexArray VAOPlayer;
	Level level;
	Tile backgroundTile;
	Texture texture;
	Texture texture2;
	Texture playerTex;

	std::vector<std::unique_ptr<Texture>> frames;
	std::vector<std::unique_ptr<Texture>> runningFrames;
	float dt;
	float currentTime = 0.0f;
	float lastTime;

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

	float playerScreenX;
	float playerScreenY;
	float playerMiddle;

	float leftBound = (screenWidth / 2) - (screenWidth /2 ) * 0.1; // Left threshold for screen to begin scrolling
	float rightBound = (screenWidth / 2) + (screenWidth / 2) * 0.1;// Right threshold
	float* tileVert;
	float* playerVert;
	void composeFrame();
	bool gameRunning = true;
	bool drawTriangle = true;

	float leftRightMove = 0.0f;

	glm::mat4 MVP_Scene;
	glm::mat4 proj;
	glm::mat4 model;
	glm::mat4 view;
	
	glm::mat4 MVP_Player;
	glm::mat4 playerModel;
	glm::mat4 playerView;

	std::vector<char> board;

	void do_collisions();
	void update_dt();

	// Temporary stuff lol for testing
	float currentX = 0.0f;
	float lastX = 0.0f;
	float displacement = currentX - lastX;
	float currentTileX = 0.0f;
	float tileDisplacement = 0.0f;
	float lstTileX = 0.0f;
};

