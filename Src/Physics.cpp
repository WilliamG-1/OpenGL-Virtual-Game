#include "Physics.h"

bool Physics::entity_clamped_to_tile(Entity& e, Level& l)
{
	return 0;
}

bool Physics::is_collision_player_tile(Entity& e, Tile& t)
{
			
	return ((e.getX() + e.getWidth() - 1.0f > t.getX() && e.getX() < t.getX() + t.getWidth()) && ((e.getY() + e.getHeight() > t.getY()) && (e.getY() < t.getY() + t.getHeight())));
}


