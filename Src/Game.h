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
#include "Slime.h"
#include "Trophy.h"


enum class ArrayType {
	VERTEX = 0, ELEMENT
};

class Game
{
public:
	Game();
	~Game();
	void run();
	void processInput(Level& level);

private:	
	float screenWidth = 1024.0f;
	float screenHeight = 768.0f;
	
	double xMousePos = 0;
	double yMousePos = 0;
	float moveSpeed = 40.0f;
	float currentTexture = 0.0f;
	Window window;

	glm::vec2 playerStartingCoords = { 1.0f, 500.0f };
	Player player;
	Entity box;

	
	float dt;
	float currentTime = 0.0f;
	float lastTime;

	float a_playerFrames[3] = { 0.0f, 0.0f, 0.0f };
	float a_pigFrames[3] = { 0.0f, 0.0f, 0.0f };
	float a_appleFrame = 0.0f;

	Shader shader;
	Renderer renderer;

	unsigned int indices[6] = {
		0, 1, 2,  2, 3, 0
	};

	float playerScreenX;
	float playerScreenY;
	float playerMiddle;

	bool facing_right = true;

	float leftBound = (screenWidth / 2) - (screenWidth /2 ) * 0.1; // Left threshold for screen to begin scrolling
	float rightBound = (screenWidth / 2) + (screenWidth / 2) * 0.1;// Right threshold
	float level_displacement = 0.0f;

	float winStateTimer = 0.0f;
	
	bool cancollideleftrightlol = true;

	float leftRightMove = 0.0f;

	
	glm::mat4 MVP_Scene;
	glm::mat4 proj;
	glm::mat4 model;
	glm::mat4 view;
	
	glm::mat4 MVP_Player;
	glm::mat4 playerModel;
	glm::mat4 playerView;

	glm::mat4 pigView;
	glm::mat4 staticViewMatrix;
	glm::mat4 staticModelMatrix;
	std::vector<char> board;


	void composeFrame();
	void render_level1();
	void render_level2();
	void render_level3();
	void render_main_menu();


	void init_player_textures(float offset);
	
	void init_vertices(Entity& e, VertexArray& e_VAO, float (&vert)[20],float x, float y, float texture_x, float texture_y, float tex_right, float tex_top);
	void init_vertices(Fruit& f, VertexArray& e_VAO, float(&vert)[20], float x, float y, float texture_x, float texture_y, float tex_right, float tex_top);
	

	void update_player(GameState& gs, VertexArray& player_vao, Level& level);
	void do_player_entity_collisions();
	void do_x_collisions(GameState& gs, Level& level);
	void do_y_collisions(GameState& gs, Level& level);
	void do_player_idle_animation(int frames, float& ctr, float textureStride, float xInverseOffset);
	void do_player_running_animation(int frames, float& ctr, float xTexStride, float yTexStride = 0.315f);
	void do_pig_walk_animation(int frames, float& walkCounter, float textureStride, float yTexStride, float xInverseOffest);
	void do_pig_run_animation(int frames, float& runCounter, float xTexStride, float yTexStride, float xInverseOffset);

	void update_fruit(Fruit& fruit, VertexArray& vao, float& frame, float textureSlot, GameState& gs);
	void do_fruit_animation(int frames, float& counter, float xTextureStride);

	void update_angry_block(AngryBlock& angryBlock, VertexArray& ablock_vao, float& frame);
	void update_ablock_animations(int frames, float& counter, float xTextureStride);

	void update_slime(Slime& slime, VertexArray& slime_vao, float& frame);
	void do_slime_move_animation(int frames, float& counter, float textureStride);

	void do_win_animation(Trophy& trophy);

	// Old Stuff Lol
	void buffer_next_frame(VertexArray& vao, Texture& texture, float(&vert)[20], float space = 11 / 384);
	void init_enemy_texture(VertexArray& enemy_vao, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkingVector, std::vector<std::unique_ptr<Texture>>& runningVector, unsigned int idleFrames, unsigned int walkingFrames, unsigned int runningFrames, const std::string& idlePath, const std::string& walkPath, const std::string& runningPath);
	void init_fruit_texture(VertexArray& fruit_vao, std::vector<std::unique_ptr<Texture>>& fruitVector, unsigned int spriteCount, const std::string& path);
	void update_tiles(Level& level, VertexArray& background_vao, VertexArray& grass_vao);

	void update_pig(Pig& pig, VertexArray& pig_vao, Fruit& fruit, float& walk_frame, float& run_frame);
	void do_pig_animations(Pig& p, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkVector, std::vector<std::unique_ptr<Texture>>& runningVector, float& currentFrame);
	void do_fruit_animatinos(Fruit& fruit, std::vector<std::unique_ptr<Texture>>& frames, float& currentFrame);

	void update_trophy(Trophy& trophy, VertexArray& trophyVAO);

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

