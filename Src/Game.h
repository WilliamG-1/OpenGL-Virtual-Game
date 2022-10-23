#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameState.h"
#include "Texture.h"
#include "Level.h"
#include "Player.h"
#include "zArrayConverter.h"
#include "Tile.h"
#include "Pig.h"
#include "Physics.h"
#include "Fruit.h"
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
	float currentTexture = 0.0f;
	Window window;

	glm::vec2 playerStartingCoords = { 1.0f, 500.0f };
	Player player;
	Entity box;
	

	VertexArray VAOBackground;
	VertexArray VAOGrassBlock;
	VertexArray VAOPlayer;
	
	Level level;
	Tile backgroundTile;
	Texture backgroundTexture;
	Texture grassTexture;
	Texture pigTex;
	Texture a_PlayerTexture;
	Texture a_AppleTexture;
	
	std::vector<VertexArray> a_VAO;
	std::vector<std::unique_ptr<Texture>> airFrames;
	std::vector<std::unique_ptr<Texture>> frames;
	std::vector<std::unique_ptr<Texture>> runningFrames;
	// ------------ Enemies ----------- \\
	
	VertexArray VAOPig;
	glm::vec2 pigCoords = { 750.0f, 64.0f };
	Pig pig;
	std::vector<std::unique_ptr<Texture>> pigIdle;
	std::vector<std::unique_ptr<Texture>> pigWalk;
	std::vector<std::unique_ptr<Texture>> pigRunning;
	float pigCurrentFrame = 0.0f;

	// -------------- Fruits ------------- \\ 

	VertexArray VAOApple;
	glm::vec2 fruitCoords = { 600.0f, 85.0f };
	Fruit apple;
	std::vector<std::unique_ptr<Texture>> appleFrames;
	float appleCurrentFrame;

	glm::mat4 pigView;
	
	float dt;
	float currentTime = 0.0f;
	float lastTime;

	float a_playerFrames[3] = { 0.0f, 0.0f, 0.0f };
	float a_pigFrames[3] = { 0.0f, 0.0f, 0.0f };
	float a_appleFrame = 0.0f;
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
	float apply_matrix_transform = 1.0f;

	float leftBound = (screenWidth / 2) - (screenWidth /2 ) * 0.1; // Left threshold for screen to begin scrolling
	float rightBound = (screenWidth / 2) + (screenWidth / 2) * 0.1;// Right threshold

	float backgroundVert[20];
	float grassVert[20];
	float playerVert[20];
	float pigVert[20];
	float appleVert[20];

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

	glm::mat4 staticViewMatrix;
	glm::mat4 staticModelMatrix;
	std::vector<char> board;

	void init_player_textures(float offset);
	void init_enemy_texture(VertexArray& enemy_vao, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkingVector, std::vector<std::unique_ptr<Texture>>& runningVector, unsigned int idleFrames, unsigned int walkingFrames, unsigned int runningFrames, const std::string& idlePath, const std::string& walkPath, const std::string& runningPath);
	void init_fruit_texture(VertexArray& fruit_vao, std::vector<std::unique_ptr<Texture>>& fruitVector, unsigned int spriteCount, const std::string& path);
	void init_vertices(Entity& e, VertexArray& e_VAO, float (&vert)[20],float x, float y, float texture_x, float texture_y, float tex_right, float tex_top);
	void init_vertices(Fruit& f, VertexArray& e_VAO, float(&vert)[20], float x, float y, float texture_x, float texture_y, float tex_right, float tex_top);
	void buffer_next_frame(VertexArray& vao, Texture& texture, float(&vert)[20], float space = 11 / 384);

	void update_player();
	void do_player_entity_collisions();
	void do_x_collisions();
	void do_y_collisions();
	void do_player_idle_animation(int frames, float& ctr, float textureStride, float xInverseOffset);
	void do_player_running_animation(int frames, float& ctr, float xTexStride, float yTexStride = 0.315f);
	void do_pig_walk_animation(int frames, float& walkCounter, float textureStride, float yTexStride, float xInverseOffest);
	void do_pig_run_animation(int frames, float& runCounter, float xTexStride, float yTexStride, float xInverseOffset);

	void update_fruit(Fruit& fruit);
	void do_fruit_animation(int frames, float& counter, float xTextureStride);

	void update_tiles(Level& level);

	void update_pig(Pig& pig);
	void do_pig_animations(Pig& p, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkVector, std::vector<std::unique_ptr<Texture>>& runningVector, float& currentFrame);
	void do_fruit_animatinos(Fruit& fruit, std::vector<std::unique_ptr<Texture>>& frames, float& currentFrame);

	
	void update_texture_frame(float& variable, float dt, float max_value);
	void update_dt();
	// Temporary stuff lol for testing


	float currentX = 0.0f;
	float lastX = 0.0f;
	float displacement = currentX - lastX;
	float currentTileX = 0.0f;
	float tileDisplacement = 0.0f;
	float lstTileX = 0.0f;

	bool blending = true;
	bool pressed = false;
};

