#include "Physics.h"

bool Physics::entity_clamped_to_tile(Entity& e, Level& l)
{
	return 0;
}

bool Physics::is_collision_player_tile(Entity& e, Tile& t)
{

	return ((e.getX() + e.getWidth() > t.getX() && e.getX() < t.getX() + t.getWidth()) && ((e.getY() + e.getHeight() > t.getY()) && (e.getY() < t.getY() + t.getHeight())));
}

bool Physics::entity_right_collide_left_tile(Entity& e, Tile& t)
{
	return ((e.getX() + e.getWidth() > t.getX() && e.getX() < t.getX() + t.getWidth()) && ((e.getY() + e.getHeight() > t.getY()) && (e.getY() < t.getY() + t.getHeight())));
}

bool Physics::entity_left_collide_right_tile(Entity& e, Tile& t)
{
	return ((e.getX() < t.getX() + t.getWidth() && e.getX() + e.getWidth() > t.getX()) && ((e.getY() + e.getHeight() > t.getY()) && (e.getY() < t.getY() + t.getHeight())));
}

bool Physics::entity_top_collide_bottom_tile(Entity& e, Tile& t)
{
	return ((e.getY() + e.getHeight() > t.getY() && e.getY() < t.getY() + t.getHeight()) && ((e.getX() + e.getWidth() > t.getX()) && (e.getX() < t.getX() + t.getWidth())));
}

bool Physics::entity_bottom_collide_top_tile(Entity& e, Tile& t)
{
	return ((e.getY() < t.getY() + t.getHeight() && e.getY() + e.getHeight() > t.getY()) && ((e.getX() + e.getWidth() > t.getX()) && (e.getX() < t.getX() + t.getWidth())));
}
