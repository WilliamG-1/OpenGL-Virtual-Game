#include "Level.h"

void Level::init_grass_tiles(float screenHeight)
{
	for (int r = 0; r < get_rows(); r++)
	{
		for (int c = 0; c < get_columns(); c++)
		{
			if (board[c + (r * get_columns())] == get_grass_tile())
			{
				grassBlocks.push_back(Tile(c * 64, (screenHeight - 64) - r * 64, 64.0f, 64.0f));
			}
		}
	}
}

void Level::scroll(float playerVelocity, float dt)
{
	
	dx += playerVelocity * dt;
	//for (Tile& block : grassBlocks)
	//{
	//	block.setX(block.get_starting_x() + dx);
	//}
}

void Level::scroll(glm::mat4& viewMatrix)
{
	
}

std::vector<Tile>& Level::get_grass_blocks()
{
	return grassBlocks;
}

std::vector<char> Level::get_board() const
{
	return board;
}

int Level::get_rows()
{
	return 12;
}

int Level::get_columns()
{
	return (board.size() / get_rows());
}

float Level::get_tile_displacement_x() const
{
	return this->dx;
}

