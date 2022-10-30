#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
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
#include "Slime.h"
#include "Button.h"
#include "Trophy.h"
class GameState
{
public:
	GameState(Shader& shader);
	void set_game_state(unsigned int state);
	void load_state();

	Level& get_current_level() { return c_level; }
	std::vector<Tile>& get_current_tiles() { return v_GrassTiles; }
	std::vector<Pig>& get_current_pigs() { return v_Pigs; }
	std::vector<Fruit>& get_current_apples() { return v_Apples; }
	std::vector<Fruit>& get_current_oranges() { return v_Oranges; }
	std::vector<AngryBlock>& get_current_angry_blocks() { return v_AngryBlocks; }
	std::vector<Slime>& get_current_slimes() { return v_Slimes; }
	std::vector<Button>& get_current_buttons() { return v_Buttons; }

	Player& get_current_player() { return player; }
	Trophy& get_current_trophy() { return *trophy_ptr; }
	VertexArray& get_player_vao() { return VAOPlayer; }
	VertexArray& get_background_vao() { return VAOBackground; }
	VertexArray& get_grass_vao() { return VAOGrass; }
	VertexArray& get_pig_vao() { return VAOPig; }
	VertexArray& get_apple_vao() { return VAOApple; }
	VertexArray& get_orange_vao() { return VAOOrange; }
	VertexArray& get_angry_block_vao() { return VAOABlock; }
	VertexArray& get_slime_vao() { return VAOSlime; }
	VertexArray& get_trophy_vao() { return VAOTrophy; }
	std::vector<VertexArray>& get_current_button_vaos() { return v_VAOButtons; }

	unsigned int get_current_game_state() const { return current_state; }
	void decrease_fruit_count() { fruit_count--; }
	unsigned int get_fruit_count() const { return fruit_count; }
private:
	Shader shader;
	Level c_level;
	unsigned int current_state;
	unsigned int game_over;
	unsigned int level_1;
	unsigned int level_2;

	unsigned int fruit_count = 0;

	Player player;
	Entity box;
	Tile backgroundTile;
	std::shared_ptr<Trophy> trophy_ptr;

	std::vector<Tile> v_GrassTiles;
	std::vector<Fruit> v_Apples;
	std::vector<Fruit> v_Oranges;
	std::vector<Pig> v_Pigs;
	std::vector<AngryBlock> v_AngryBlocks;
	std::vector<Slime> v_Slimes;

	std::vector<Button> v_Buttons;
	std::vector<VertexArray> v_VAOButtons;

	VertexArray VAOPlayer;
	VertexArray VAOBackground;
	VertexArray VAOGrass;
	VertexArray VAOPig;
	VertexArray VAOApple;
	VertexArray VAOOrange;
	VertexArray VAOABlock;
	VertexArray VAOSlime;
	VertexArray VAOTrophy;

	Texture playerTexture;
	Texture backgroundTexture;
	Texture grassTexture;
	Texture pigTexture;
	Texture appleTexture;
	Texture orangeTexture;
	Texture angryBlockTexture;
	Texture slimeTexture;
	Texture trophyTexture;

	float playerVert[20];
	float backgroundVert[20];
	float grassVert[20];
	float pigVert[20];
	float appleVert[20];
	float orangeVert[20];
	float aBlockVert[20];
	float buttonVert[20];
	float slimeVert[20];
	float trophyVert[20];

	glm::mat4 MVP;
	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 model;

	void load_game_over();
	void load_level_1();
	void load_level_2();
	void load_main_menu();

	void init_vertices(Entity& e, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height);
	void init_vertices(Fruit& f, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height);
	void init_vertices(Button& b, VertexArray& b_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height);
	
	

	std::vector<char> level1 = {
		//   1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 1 
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 2
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 3
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 4
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 5
		'-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', '-', '-', '-', 'X', '-', '-', '-', '-', '-', // 6
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', // 7
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 8
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', // 9
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 10
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 11
		'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', // 12
	};
	std::vector<char> level2 = {
		//   1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 1 
		'-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 2
		'-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '-', '-', 'X', '-', '-', '-', // 3
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 4
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 5
		'-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 6
		'-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 7
		'-', '-', '-', '-', 'X', '-', '-', '-', 'X', '-', '-', 'X', '-', '-', '-', 'X', 'X', 'X', '-', '-', // 8
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', // 9
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 10
		'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 11
		'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', // 12
	};
	unsigned int indices[6] = { 0, 1, 2,  2, 3, 0 };
};
