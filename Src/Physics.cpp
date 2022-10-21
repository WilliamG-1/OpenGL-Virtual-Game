#include "Physics.h"

bool Physics::entity_clamped_to_tile(Entity& e, Level& l)
{
	return 0;
}

bool Physics::is_collision_player_tile(Entity& player, Tile& t)
{ 
			// Right Player  BoxTo left Tile Box                 ||  Left Player Box to Right Tile Box				||  Top Player Box to Bottom Tile Box                      || Bottom Player Box to Top Tile Box
	return ((player.getX() + player.getWidth() - 2.0f > t.getX() && player.getX() + 2.0f < t.getX() + t.getWidth()) && ((player.getY() + player.getHeight() - 2.0f > t.getY()) && (player.getY() < t.getY() + t.getHeight())));
}


