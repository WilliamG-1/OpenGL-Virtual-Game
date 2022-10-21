#pragma once
#include "Entity.h"
#include "Level.h"
#include "Tile.h"
class Physics
{
public:
	
	static bool entity_clamped_to_tile(Entity& e, Level& l);
	static bool is_collision_player_tile(Entity& player, Tile& t);

private:
	Physics() {}
};
