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
#include "Pig.h"
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
	Player hitbox;
	

	VertexArray VAO;
	VertexArray VAOPlayer;
	VertexArray VAOPig;
	Level level;
	Tile backgroundTile;
	Texture texture;
	Texture texture2;
	
	std::vector<std::unique_ptr<Texture>> airFrames;
	std::vector<std::unique_ptr<Texture>> frames;
	std::vector<std::unique_ptr<Texture>> runningFrames;
	// ------------ Enemies ----------- \\
	
	glm::vec2 pigCoords = { 750.0f, 64.0f };
	Pig pig;
	std::vector<std::unique_ptr<Texture>> pigIdle;
	std::vector<std::unique_ptr<Texture>> pigWalk;
	std::vector<std::unique_ptr<Texture>> pigRunning;

	float pigCurrentIdleFrame = 0.0f;
	glm::mat4 pigView;
	
	float dt;
	float currentTime = 0.0f;
	float lastTime;

	float idleFrame = 0.0f;
	float runningFrame = 0.0f;

	Shader shader;
	//Shader shader2;
	Renderer renderer;

	unsigned int indices[6] = {
		0, 1, 2,  2, 3, 0
	};

	float playerScreenX;
	float playerScreenY;
	float playerMiddle;
	float pastX;
	float pastY;
	bool updatePastX = true;
	bool updatePastY = true;
	bool facing_right = true;

	float leftBound = (screenWidth / 2) - (screenWidth /2 ) * 0.1; // Left threshold for screen to begin scrolling
	float rightBound = (screenWidth / 2) + (screenWidth / 2) * 0.1;// Right threshold

	float tileVert[20];
	float playerVert[20];
	float pigVert[20];

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

	void init_player_textures();
	void init_enemy_texture(VertexArray& enemy_vao, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkingVector, std::vector<std::unique_ptr<Texture>>& runningVector, unsigned int idleFrames, unsigned int walkingFrames, unsigned int runningFrames, const std::string& idlePath, const std::string& walkPath, const std::string& runningPath);
	void init_vertices(Entity& entity, VertexArray& e_VAO, float (&vert)[20],float x, float y, float tex_left, float tex_right, float tex_width, float tex_height);
	void do_collisions();
	void do_x_collisions();
	void do_y_collisions();
	void update_texture_frame(float& variable, float dt, float max_value);
	void update_dt();
	// Temporary stuff lol for testing
	float currentX = 0.0f;
	float lastX = 0.0f;
	float displacement = currentX - lastX;
	float currentTileX = 0.0f;
	float tileDisplacement = 0.0f;
	float lstTileX = 0.0f;
};

