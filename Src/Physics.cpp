#include "Physics.h"

bool Physics::entity_clamped_to_tile(Entity& e, Level& l)
{
	return 0;
}

bool Physics::is_collision_player_tile(Entity& player, Tile& t)
{ 
			// Right Player  BoxTo left Tile Box                 ||  Left Player Box to Right Tile Box				||  Top Player Box to Bottom Tile Box                      || Bottom Player Box to Top Tile Box
	return ((player.getX() + player.getWidth() - 2.0f > t.getX() && player.getX() + 2.0f < t.getX() + t.getWidth()) && ((player.getY() + player.getHeight() > t.getY()) && (player.getY() < t.getY() + t.getHeight())));
}

bool Physics::is_collision_player_entity(Entity& player, Entity& e)
{                  
	return (((player.getX() + player.getWidth() - 9.0f) > (e.getX() + 20.0f)) &&		// Right Player Box to Left Entity Box
			 (player.getX() + 9.0f < (e.getX() + e.getWidth() - 20.0f)) &&				// Left Player Box to Right Entity Box	
			((player.getY() + player.getHeight() - 9.0f) > (e.getY() + 10.0f)) &&	    // Top Player Box to Bottom Entity box
			 (player.getY() + 9.0f < (e.getY() + e.getHeight() - 15.0f)));				// Bottom Player Box to Top Entity Box
}


