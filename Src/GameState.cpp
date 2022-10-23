#include "GameState.h"

GameState::GameState()
	:
	player(1.0f, 200.0f, 64.0f, 64.0f)
{

}

void GameState::set_game_state(unsigned int state)
	
{
	current_state = state;
}

void GameState::load_state()
{
	if (current_state == 0)
		load_game_over();
	if (current_state == 1)
		load_level_1();
}

void GameState::draw(Renderer& renderer, Shader& shader)
{
	switch (current_state)
	{
	case 0: // Game Over
		break;

	case 1: // Level 1

		break;
	}
}

void GameState::load_level_1()
{
	Level level;
	level.init_level_layout(level1);
	// Load Player
	
	// Load Tiles

	// Load Enemies

	// Load Fruits


}


void GameState::load_game_over()
{

}


