#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Physics.h"
#include "zArrayConverter.h"
#include "Texture.h"
#include "Player.h"
#include "Tile.h"
#include "Pig.h"
#include "Fruit.h"
#include "AngryBlock.h"

class GameState
{
public:
	GameState();
	void set_game_state(unsigned int state);
	void load_state();
	void draw(Renderer& renderer, Shader& shader);

	Level& get_current_level() { return c_level; }
	std::vector<Tile>& get_current_tiles() { return v_GrassTiles; }
	std::vector<Pig>& get_current_pigs() { return v_Pigs; }
	std::vector<Fruit>& get_current_apples() { return v_Apples; }
	std::vector<Fruit>& get_current_oranges() { return v_Oranges; }
	std::vector<AngryBlock>& get_current_angry_blocks() { return v_AngryBlocks; }


	Player& get_current_player() { return player; }

	VertexArray& get_player_vao() { return VAOPlayer; }
	VertexArray& get_background_vao() { return VAOBackground; }
	VertexArray& get_grass_vao() { return VAOGrass; }
	VertexArray& get_pig_vao() { return VAOPig; }
	VertexArray& get_apple_vao() { return VAOApple; }
	VertexArray& get_orange_vao() { return VAOOrange; }
	VertexArray& get_angry_block_vao() { return VAOABlock; }
	unsigned int get_current_state() const { return current_state; }
private:
	Level c_level;
	unsigned int current_state;
	unsigned int game_over;
	unsigned int level_1;
	unsigned int level_2;

	Player player;
	Entity box;
	Tile backgroundTile;

	std::vector<Tile> v_GrassTiles;
	std::vector<Fruit> v_Apples;
	std::vector<Fruit> v_Oranges;
	std::vector<Pig> v_Pigs;
	std::vector<AngryBlock> v_AngryBlocks;
	
	VertexArray VAOPlayer;
	VertexArray VAOBackground;
	VertexArray VAOGrass;
	VertexArray VAOPig;
	VertexArray VAOApple;
	VertexArray VAOOrange;
	VertexArray VAOABlock;


	Texture playerTexture;
	Texture backgroundTexture;
	Texture grassTexture;
	Texture pigTexture;
	Texture appleTexture;
	Texture orangeTexture;
	Texture angryBlockTexture;

	float playerVert[20];
	float backgroundVert[20];
	float grassVert[20];
	float pigVert[20];
	float appleVert[20];
	float orangeVert[20];
	float aBlockVert[20];

	glm::mat4 MVP;
	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 model;
	void load_game_over();
	void load_level_1();

	void init_vertices(Entity& e, VertexArray& e_VAO, float(&vert)[20], float x, float y, float texture_x, float texture_y, float tex_right, float tex_top);
	void init_vertices(Fruit& f, VertexArray& e_VAO, float(&vert)[20], float x, float y, float texture_x, float texture_y, float tex_right, float tex_top);
	
	std::vector<char> level1 = {
		//   1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', //1 
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 1
			'X', 'X', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 3
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 4
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 5
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 6
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 7
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', '-', '-', // 8
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', // 9
			'-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 10
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 11
			'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', // 12
	};
	unsigned int indices[6] = { 0, 1, 2,  2, 3, 0 };
};
