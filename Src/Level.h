#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Tile.h"

class Level
{
public:
	void init_grass_tiles(float screenHeight);
	void scroll(float player_velocity, float dt);
	void scroll(glm::mat4& viewMatrix);
	std::vector<char>& get_board();
	std::vector<Tile>& get_grass_blocks();
	void init_level_layout(const std::vector<char>& layout) { board = layout; }

	int get_rows();
	int get_columns();
	float get_tile_displacement_x() const;

	char get_background_tile() const { return '-'; }
	char get_grass_tile() const { return 'X'; }
private:	
	std::vector<Tile> grassBlocks;
	//	 0 Marks an Empty Tile, X marks a tile where block placed
	//   [Rows][Columns]
	std::vector<char> board = {
		//   1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19   20 
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', //1 
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 1
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 3
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 4
			'-', '-', '-', '-', '-', '-', '-', '-', 'X', 'X', '-', '-', 'X', '-', '-', '-', '-', '-', '-', '-', // 5
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 6
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 7
			'-', '-', '-', '-', '-', 'X', 'X', '-', '-', '-', '-', '-', '-', '-', 'X', 'X', 'X', 'X', '-', '-', // 8
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', 'X', '-', '-', '-', '-', '-', '-', // 9
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 10
			'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', // 11
			'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', // 12
	};
	
	
	float dx = 0.0f;
};

