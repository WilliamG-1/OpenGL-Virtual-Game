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

bool Physics::is_collision_player_entity_f(Player& player, Entity& e, float p_offset, float e_lr_offset, float e_u_offset, float e_d_offset)
{                  
	return (((player.getX() + player.getWidth() - p_offset) > (e.getX() + e_lr_offset)) &&		// Right Player Box to Left Entity Box
			 (player.getX() + p_offset < (e.getX() + e.getWidth() - e_lr_offset)) &&				// Left Player Box to Right Entity Box	
			((player.getY() + player.getHeight() - p_offset) > (e.getY() + e_d_offset)) &&	    // Top Player Box to Bottom Entity box
			 (player.getY() + p_offset < (e.getY() + e.getHeight() - e_u_offset)));				// Bottom Player Box to Top Entity Box
}

bool Physics::is_collision_player_entity_a(Player& player, Entity& e)
{
	return (((player.getX() + player.getWidth()) > (e.getX())) &&		// Right Player Box to Left Entity Box
			 (player.getX() < (e.getX() + e.getWidth())) &&				// Left Player Box to Right Entity Box	
			((player.getY() + player.getHeight()) > (e.getY())) &&	    // Top Player Box to Bottom Entity box
			(player.getY() < (e.getY() + e.getHeight())));				// Bottom Player Box to Top Entity Box
}

bool Physics::is_collision_player_fruit(Player& player, Fruit& fruit)
{
	return (
			player.getX() + player.getWidth() > fruit.getX()  && // Right Player Box to Left Fruit Box
			player.getX() < fruit.getWidth() + fruit.getX()   && // Left Player Box to Right Fruit Box
			player.getY() + player.getHeight() > fruit.getY() && // Top Player Box to Bottom Fruit Box
			player.getY() < fruit.getHeight() + fruit.getY()     // Bottom Player Box to Top Fruit Box
		);
}

bool Physics::mouse_inside_button(double xMousePos, double yMousePos, Button& button)
{
	return (
			   xMousePos >= button.getX()						&&
			   xMousePos <= button.getX() + button.getWidth()	&&
			   yMousePos >= button.getY()						&&
			   yMousePos <= button.getY() + button.getHeight()
		   );
}



