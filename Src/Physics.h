#pragma once
#include "Entity.h"
#include "Fruit.h"
#include "Player.h"
#include "Level.h"
#include "Tile.h"
class Physics
{
public:
	
	static bool entity_clamped_to_tile(Entity& e, Level& l);
	static bool is_collision_player_tile(Entity& player, Tile& t);
	static bool is_collision_player_entity(Player& player, Entity& e);
	static bool is_collision_player_fruit(Player& player, Fruit& fruit);
private:
	Physics() {}
};
