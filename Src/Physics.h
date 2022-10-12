#pragma once
#include "Entity.h"
#include "Level.h"
#include "Tile.h"
class Physics
{
public:
	Physics();
	static bool entity_clamped_to_tile(Entity& e, Level& l);
	static bool is_collision_player_tile(Entity& e, Tile& t);
	static bool entity_right_collide_left_tile(Entity& e, Tile& t);
	static bool entity_left_collide_right_tile(Entity& e, Tile& t);
	static bool entity_top_collide_bottom_tile(Entity& e, Tile& t);
	static bool entity_bottom_collide_top_tile(Entity& e, Tile& t);
private:
	static float gravity;

};
