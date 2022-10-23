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


class GameState
{
public:
	GameState();
	void set_game_state(unsigned int state);
	void load_state();
	void draw(Renderer& renderer, Shader& shader);
	std::vector<Tile>& get_current_tiles() { return v_GrassTiles; }
	std::vector<Pig>& get_current_pigs() { return v_Pigs; }
	std::vector<Fruit>& get_current_apples() { return v_Apples; }
	Player& get_current_player() { return player; }

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
	std::vector<Pig> v_Pigs;
	std::vector<Fruit> v_Apples;
	
	VertexArray VAOPlayer;
	VertexArray VAOBackground;
	VertexArray VAOGrass;
	VertexArray VAOPig;
	VertexArray VAOApple;

	Texture playerTexture;
	Texture backgroundTexture;
	Texture grassTexture;
	Texture pigTexture;
	Texture appleTexture;

	float playerVert[20];
	float backgroundVert[20];
	float grassVert[20];
	float pigVert[20];
	float appleVert[20];

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
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 3
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 4
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 5
			'-', '-', '-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 6
			'-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 7
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 8
			'-', 'X', '-', '_', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 9
			'-', '-', 'X', '_', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 10
			'-', '-', '-', '_', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 11
			'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', // 12
	};
	unsigned int indices[6] = { 0, 1, 2,  2, 3, 0 };
};
