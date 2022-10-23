#pragma once
#include <vector>
#include <memory>
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

	unsigned int get_current_state() const { return current_state; }
private:
	Level c_level;
	unsigned int current_state;
	unsigned int game_over;
	unsigned int level_1;
	unsigned int level_2;

	Player player;
	Tile backgroundTile;
	std::vector<Tile> v_grassTiles;
	std::vector<Pig> v_Pigs;
	std::vector<Fruit> v_apples;

	void load_game_over();
	void load_level_1();

	void init_enemy_texture(VertexArray& enemy_vao, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkingVector, std::vector<std::unique_ptr<Texture>>& runningVector, unsigned int idleFrames, unsigned int walkingFrames, unsigned int runningFrames, const std::string& idlePath, const std::string& walkPath, const std::string& runningPath);
	void init_fruit_texture(VertexArray& fruit_vao, std::vector<std::unique_ptr<Texture>>& fruitVector, unsigned int spriteCount, const std::string& path);
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
			'-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 9
			'-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 10
			'-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 11
			'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', // 12
	};
};
