#include "Game.h"
#include <iostream>
#include <iomanip>
#define WIDNOW_WIDTH = 1024.0F
#define WINDOW_HEIGHT = 768.0F
int gameLevel = 0;
bool gameRunning = true;

Game::Game()
	:
	player(playerStartingCoords.x, playerStartingCoords.y, 64.0f, 64.0f), box(0.0f, 0.0f, 64.0f, 64.0f),
	window(screenWidth, screenHeight, "OpenGl Game"),
	model(1.0f), view(1.0f), proj(1.0f),
	MVP_Scene(1.0f), MVP_Player(1.0f),
	playerModel(1.0f), playerView(1.0f), staticViewMatrix(1.0f), staticModelMatrix(1.0f),
	pigView(1.0f)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Either exit game or return to main menu when excape key is pressed
	
	glfwSetKeyCallback(window.getWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			if (gameLevel > 1)
				gameLevel--;					
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			if (gameLevel > 0 && gameLevel < 2)
				gameLevel++;
		}
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			if (gameLevel == 0)
				gameLevel = -1;
			else
				gameLevel = 0;
		}
	});
	std::string vertSource;
	std::string fragSource;
	// Read the contents of the shaders into our strings
	shader.readShaderFile("Shaders/Vertex.vert", vertSource);
	shader.readShaderFile("Shaders/Fragment.frag", fragSource);

	// Initialize our shader by passing the source code
	shader.initShaders(vertSource, fragSource);

	// Finally, use our shader program
	shader.use();
}

void Game::run()
{
	
	while (gameRunning)
	{
		if (gameLevel == -1)		
			gameRunning = false;	// Quit Game
		if (gameLevel == 0)
			render_main_menu();		// Main Menu
		if (gameLevel == 1)
			render_level1();		// Level 1
		if (gameLevel == 2)
			render_level2();		// Level 2
		
	}

	// Destroy stuff
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}
void Game::render_main_menu()
{
	
	shader.setUniform1f("u_xTextureOffset", 0.0f);
	shader.setUniform1f("u_yTextureOffset", 0.0f);
	shader.setUniform1f("u_xInverseoffset", 0.0f);
	shader.setUniform1f("facing_right", 1.0f);

	proj = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
	view = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	MVP_Scene = model * proj * view;
	shader.setUniformMat4f("u_MVP", MVP_Scene);
	GameState menu(shader);
	menu.set_game_state(0);
	menu.load_state();
	while (gameLevel == 0)
	{
		// Clear Screen
		glClearColor(0.15f, 0.32f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		renderer.draw(menu.get_current_button_vaos()[0], shader);

		if (glfwGetKey(window.getWindow(), GLFW_KEY_1) == GLFW_PRESS)
		{
			gameLevel = 1;
			menu.set_game_state(1);
		}
		glfwGetCursorPos(window.getWindow(), &xMousePos, &yMousePos);
		
		
		if (Physics::mouse_inside_button(xMousePos, yMousePos, menu.get_current_buttons()[0]) && glfwGetMouseButton(window.getWindow(), GLFW_MOUSE_BUTTON_1 == GLFW_PRESS))
			gameLevel = 1;
	
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
		update_dt();
	}


}
void Game::render_level1()
{
	
	GameState gs(shader);
	gs.set_game_state(1);
	gs.load_state();
	player = gs.get_current_player();
	gs.get_current_level().init_grass_tiles(768.0f);
	board = gs.get_current_level().get_board();
	composeFrame();
	//update_player(gs, gs.get_player_vao(), gs.get_current_level());

	while (gameLevel == 1)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		update_tiles(gs.get_current_level(), gs.get_background_vao(), gs.get_grass_vao());
		

		for (Slime& slime : gs.get_current_slimes())
			update_slime(slime, gs.get_slime_vao(), slime.get_current_walk_frame());

		for (Fruit& fruit : gs.get_current_oranges())
			update_fruit(fruit, gs.get_orange_vao(), fruit.get_frame(), 5);
		update_player(gs, gs.get_player_vao(), gs.get_current_level());

		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
		update_dt();
		level_displacement = gs.get_current_level().get_tile_displacement_x();
	}
}
void Game::render_level2()
{
	
	GameState gs(shader);
	gs.set_game_state(2);
	gs.load_state();
	player = gs.get_current_player();
	gs.get_current_level().init_grass_tiles(768.0f);
	board = gs.get_current_level().get_board();
	composeFrame();
	while (gameLevel == 2)
	{

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// Clear Screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ========================= ImGui ==============================
		ImGui::Begin("Window");
		ImGui::Text("Player Coordinates: (%.2f., %.2f)", player.getX(), player.getY());
		ImGui::Text("Player Velocity: (%.2f, %.2f)", player.getVx(), player.getVy());
		//ImGui::Text("Tile: (%.2f, %.2f)", gs.get_grass_blocks()[0].getX(), gs.get_grass_blocks()[0].getY());
		ImGui::Text("Tile Displacement: %.2f", level_displacement);
		ImGui::Text("Player is moving: %d$", player.is_moving());
		ImGui::Text("Player Screen Coords: (%.2f, %.2f)", playerScreenX, playerScreenY);
		ImGui::Text("Bounds: (%.2f, %.2f)", leftBound, rightBound);
		ImGui::Text("pCenter = %.2f", playerMiddle);
		ImGui::Text("frame: %.2f", a_playerFrames[0]);
		ImGui::End();

		// <=========================== Rendering Code ==========================> \\

		update_tiles(gs.get_current_level(), gs.get_background_vao(), gs.get_grass_vao());

		// Update all pigs
		for (auto& pig : gs.get_current_pigs())					
			update_pig(pig, gs.get_pig_vao(), gs.get_current_apples()[0], pig.get_walk_frame(), pig.get_run_frame());

		// Update all angry blocks
		for (auto& angryblock : gs.get_current_angry_blocks())
			update_angry_block(angryblock, gs.get_angry_block_vao(), angryblock.get_blink_frame());
		
		// Update all apples
		for (auto& apple : gs.get_current_apples())
			update_fruit(apple, gs.get_apple_vao(), apple.get_frame(), 3.0f);

		// Update all oranges
		for (auto& orange : gs.get_current_oranges())
			update_fruit(orange, gs.get_orange_vao(), orange.get_frame(), 5.0f);

		//update_angry_block(gs.get_current_angry_blocks()[0], gs.get_angry_block_vao(), gs.get_current_angry_blocks()[0].get_blink_frame());
		update_player(gs, gs.get_player_vao(), gs.get_current_level());

		//update_fruit(gs.get_current_apples()[0], gs.get_apple_vao(), gs.get_current_apples()[0].get_frame());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
		update_dt();
		level_displacement = gs.get_current_level().get_tile_displacement_x();
	}
}
void Game::processInput(Level& level)
{

	if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS && gameLevel > 0)
	{
		gameLevel = 0;
	}


	// Left Movement
	if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		facing_right = false;
		//runningFrames[runningFrame]->bind();
		player.set_moving_right_state(false);
		player.set_moving_left_state(true);
		if (player.can_move_left())
		{
			if (playerMiddle < leftBound && level_displacement <= 0)
			{
				player.setVx(-moveSpeed);
				level.scroll(moveSpeed, dt);
			}
			else {

				playerScreenX -= moveSpeed * dt;
				player.setVx(-moveSpeed);
			}
		}
	}

	// Right Movement
	else if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		facing_right = true;
		//runningFrames[runningFrame]->bind();
		player.set_moving_left_state(false);
		player.set_moving_right_state(true);
		if (player.can_move_right())
		{
			if (playerMiddle > rightBound && level_displacement >= -256)
			{
				player.setVx(moveSpeed);
				level.scroll(-moveSpeed, dt);
			}
			else {
				playerScreenX += moveSpeed * dt;
				player.setVx(moveSpeed);
				player.set_moving_right_state(true);
			}
		}
	}
	else
	{
		//frames[idleFrame]->bind();
		player.setVx(0);
		player.set_moving_right_state(false);
		player.set_moving_left_state(false);
	}


	// Jumping
	if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && player.can_move_up())
	{
		player.jump(dt);
		player.set_can_jump(false);
		player.set_moving_up_state(true);
		player.set_can_move_down(true);
		player.set_falling_state(false);
	}
	if (player.getVy() < 0)
	{
		player.set_moving_up_state(false);
		player.set_falling_state(true);
		//airFrames[1]->bind();
	}
	if (facing_right) shader.setUniform1f("facing_right", 1.0f);
	else shader.setUniform1f("facing_right", 0.0f);


	// Blending


}  
void Game::composeFrame()
{		
	// <-------------------- Uniform Stuff ------------------------> \\
	
	playerScreenX = player.getX();
	MVP_Player = playerModel * proj * playerView;
	playerView = glm::translate(glm::mat4(1.0f), glm::vec3(playerScreenX, playerScreenY, 0.0f));
	playerMiddle = (playerScreenX + playerScreenX + player.getWidth()) / 2;

	proj = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
	view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
	MVP_Scene = model * proj * view;
	MVP_Player = playerModel * proj * playerView;
	shader.setUniformMat4f("u_MVP", MVP_Scene);
} 

void Game::update_player(GameState& gs, VertexArray& player_vao, Level& level)
{
	playerView = glm::translate(playerModel, glm::vec3(playerScreenX, player.getY(), 0.0f));

	player.moveX(dt);
	do_x_collisions(gs, level);
	player.moveY(dt);
	do_y_collisions(gs, level);
	playerMiddle = (playerScreenX + playerScreenX + player.getWidth()) / 2;

	MVP_Player = playerModel * proj * playerView;

	processInput(level);
	shader.setUniformMat4f("u_MVP", MVP_Player);
	shader.setUniform1f("currentTex", 1.0f);
	if (player.getVx() == 0) do_player_idle_animation(10, a_playerFrames[0], 0.0833, 0.08f);
	else do_player_running_animation(11, a_playerFrames[1], 0.0833f, 0.325f);
	renderer.draw(player_vao, shader);

}
void Game::do_player_entity_collisions()
{
	// To do
}
void Game::do_x_collisions(GameState& gs, Level& level)
{
	if (player.getX() <= 0.05f && player.is_moving_left())
	{
		player.setX(0.05f);
		playerScreenX = 0.05f;
	}
	if (player.getX() + player.getWidth() >= 1276)
	{
		player.setX(1276 - 64);
		playerScreenX = (screenWidth - 64);
	}
	for (auto& tile : level.get_grass_blocks())
	{

		if (Physics::is_collision_player_tile(player, tile) && player.is_moving_left())
		{
			//updatePastX = false;
			//player.set_can_move_left(false);
			player.setX(player.getX() + (tile.getX() + tile.getWidth() - player.getX()));
			playerScreenX = playerScreenX + (tile.getX() + level_displacement + tile.getWidth() - playerScreenX);
			//player.setX(pastX);
			//playerScreenX = pastX;
		}
		
		if (Physics::is_collision_player_tile(player, tile) && player.is_moving_right())
		{
			player.setX(player.getX() - (player.getX() + player.getWidth() - tile.getX()));
			playerScreenX = playerScreenX - (playerScreenX + player.getWidth() - tile.getX() - level_displacement);
			//playerScreenX = 
		}
	}

	// Check for collisions with Angry block (moving)
	for (auto& angryblock : gs.get_current_angry_blocks())
	{
		if (Physics::is_collision_player_entity_a(player, angryblock) && player.is_moving_left() && cancollideleftrightlol)
		{
			player.setX(player.getX() + (angryblock.getX() + angryblock.getWidth() - player.getX()));	// Set the players x coordinate by subtracting the distance traveled "inside" the object from the current x coordinate; Essentially resets to outside the entity						
			playerScreenX = playerScreenX + (angryblock.getX() + level_displacement + angryblock.getWidth() - playerScreenX);

		}

		if (Physics::is_collision_player_entity_a(player, angryblock) && player.is_moving_right() && cancollideleftrightlol)
		{
			player.setX(player.getX() - (player.getX() + player.getWidth() - angryblock.getX()));
			playerScreenX = playerScreenX - (playerScreenX + player.getWidth() - angryblock.getX() - level_displacement);

		}
	}

	player.applyGravity(dt);
}
void Game::do_y_collisions(GameState& gs, Level& level)
{
	for (auto& tile : level.get_grass_blocks())
	{
		if (Physics::is_collision_player_tile(player, tile))
		{

			if (Physics::is_collision_player_tile(player, tile) && player.is_falling())
			{
				//updatePastY = false;
				//player.set_falling_state(false);
				player.set_can_move_down(false);
				player.setVy(5.0f);
				player.set_can_jump(true);
				//player.set_moving_up_state(false);
				player.set_can_move_down(false);
				player.setY(player.getY() + (tile.getY() + tile.getHeight() - player.getY()));
				//playerScreenY(player.getY() + (tile.getY() + tile.getHeight() - player.getY()))
			}
			if (Physics::is_collision_player_tile(player, tile) && player.is_jumping())
			{
				player.setVy(0);
				player.setY(player.getY() - (player.getY() + player.getHeight() - tile.getY()));
				player.set_can_move_down(true);
			}
			else {
				//player.set_can_move_down(false);
				//jkplayer.set_falling_state(true);
			}
		}
	}

	// angry block dude collisions
	for (auto& angryblock : gs.get_current_angry_blocks())
	{
		
		if (Physics::is_collision_player_entity_f(player, angryblock, 0.0f, 0.0f, -15.0f, 0.0f) && player.is_falling())
		{
			cancollideleftrightlol = false;
			player.set_can_move_down(false);
			player.setVy(0.0f);
			player.set_can_jump(true);
			player.set_can_move_down(false);
			player.setY(angryblock.getY() + angryblock.getHeight() + 1.0f);
		}
		else cancollideleftrightlol = true;
		if (Physics::is_collision_player_entity_f(player, angryblock, 0.0f, 0.0f, 0.0f, -9.0f) && player.is_jumping())
		{
			cancollideleftrightlol = false;
			player.setVy(-angryblock.getYVelocity() * dt * 2);
			player.setY(angryblock.getY() - player.getHeight() - (angryblock.getYVelocity() * dt) - 0.6);
			player.set_can_move_down(true);
		}
		else cancollideleftrightlol = true;
		
	}
	
}
void Game::do_player_idle_animation(int frames, float& counter, float stride, float xInverseOffset)
{
	counter += dt * 1.8;
	shader.setUniform1f("u_xInverseOffset", xInverseOffset);
	shader.setUniform1f("u_yTextureOffset", 0.0f);
	if ((int)counter > frames)
	{
		counter = 0.0f;
	}
	shader.setUniform1f("u_xTextureOffset", (float)((int)counter) * stride);
}
void Game::do_player_running_animation(int frames, float& counter, float xTexStride, float yTexStride)
{
	counter += dt * 1.8;
	shader.setUniform1f("u_xInverseOffset", 0.0f);
	shader.setUniform1f("u_yTextureOffset", yTexStride);
	if ((int)counter > frames)
	{
		counter = 0.0f;
	}
	shader.setUniform1f("u_xTextureOffset", (float)((int)counter) * xTexStride);
}

void Game::update_tiles(Level& level, VertexArray& background_vao, VertexArray& grass_vao)
{
	shader.setUniform1f("currentTex", 0.0f);
	shader.setUniform1f("u_xTextureOffset", 0.0f);
	shader.setUniform1f("u_yTextureOffset", 0.0f);
	shader.setUniform1f("u_xInverseOffset", 0.0f);
	shader.setUniform1f("facing_right", 1.0f);
	shader.setUniformMat4f("u_MVP", MVP_Scene);
	
	for (int r = 0; r < level.get_rows(); r++)
	{
		for (int c = 0; c < level.get_columns(); c++)
		{
			view = glm::translate(model, glm::vec3(level_displacement + (64 * c), -(64 * r), 0.0f));
			MVP_Scene = model * proj * view;
			shader.setUniformMat4f("u_MVP", MVP_Scene);

			if (board[c + (r * level.get_columns())] == level.get_grass_tile())
			{
				shader.setUniform1f("currentTex", 4.0f);
				renderer.draw(grass_vao, shader);
			}

			if (board[c + (r * level.get_columns())] == level.get_background_tile())
			{
				shader.setUniform1f("currentTex", 0.0f);
				renderer.draw(background_vao, shader);
			}
		}
	}
}

void Game::update_slime(Slime& slime, VertexArray& slime_vao, float& frame)
{
	if (slime.getXVelocity() > 0)
		shader.setUniform1f("facing_right", 0.0f);	// Invert sprite texture if moving right
	else shader.setUniform1f("facing_right", 1.0f); // Invert sprite texture if moving left
	shader.setUniform1f("currentTex", 7.0f);		// Select the correct texture slot in the fragment shader

	slime.move(dt);									// What could this function do??? Very cryptic......
	do_slime_move_animation(10, slime.get_current_walk_frame(), 0.1);	// update the slimes frames. Slime texture atlas has a total of 15 frames

	//playerView = glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 1.0f)) * glm::translate(model, glm::vec3(slime.getX() + level_displacement, slime.getY(), 0.0f));;
	playerView = glm::translate(model, glm::vec3(slime.getX() + level_displacement, slime.getY(), 0.0f)); // Translate the view matrix based on slime position and level displacement (to accomodate scrolling)
	
	MVP_Scene = model * proj * playerView; 			// Compose the MVP with the new view matrix
	shader.setUniformMat4f("u_MVP", MVP_Scene);		// Send the new MVP matrix to the vertex shader to update position

	renderer.draw(slime_vao, shader);				// Finally, draw the slime
}
void Game::do_slime_move_animation(int frames, float& counter, float textureStride)
{
	counter += dt * .7;		// update the frame counter
	if ((int)counter > frames )	// When counter gets bigger than the current number of frames, reset it to 0
		counter = 0.0f;
	shader.setUniform1f("u_xTextureOffset", (float)(int)counter * textureStride);	// Calculate the texture offset (between frames in the texture atlas), then send it to the vertex shader
	shader.setUniform1f("u_xInverseOffset", 0);	// No inverse offset 
	shader.setUniform1f("u_yTextureOffset", 0); // No y offset
}

void Game::update_pig(Pig& pig, VertexArray& pig_vao, Fruit& fruit, float& walk_frame, float& run_frame)
{
	if (pig.getXVelocity() > 0)
		shader.setUniform1f("facing_right", 0.0f);
	else shader.setUniform1f("facing_right", 1.0f);
	shader.setUniform1f("currentTex", 2.0f);
	if (!pig.is_enraged())
	{
		pig.check_fruit_existance(fruit);
		//0.005208333333, 0.5f, 0.05729f, 0.25f

		do_pig_walk_animation(14, pig.get_walk_frame(), 0.0625f, 0.0f, 0.05729 + 0.0052f);
	}
	else {
		do_pig_run_animation(10, pig.get_run_frame(), 0.0625f, 0.25f, 5 * (0.05729 + 0.0052f));
	}

	pig.move(dt);
	pigView = glm::translate(model, glm::vec3(pig.getX() + level_displacement, pig.getY(), 0.0f));
	MVP_Scene = model * proj * pigView;
	shader.setUniformMat4f("u_MVP", MVP_Scene);
	renderer.draw(pig_vao, shader);

}
void Game::do_pig_walk_animation(int frames, float& walkCounter, float textureStride, float yTexStride, float xInverseOffest)
{
	walkCounter += dt * 1.8;
	shader.setUniform1f("u_xInverseOffset", xInverseOffest);
	shader.setUniform1f("u_yTextureOffset", yTexStride);
	if ((int)walkCounter > frames)
		walkCounter = 0.0f;
	shader.setUniform1f("u_xTextureOffset", (float)((int)walkCounter) * textureStride);
}
void Game::do_pig_run_animation(int frames, float& runCounter, float xTexStride, float yTexStride, float xInverseOffset)
{
	shader.setUniform1f("u_xInverseOffset", xInverseOffset);
	runCounter += dt * 1.8;
	shader.setUniform1f("u_yTextureOffset", yTexStride);
	if ((int)runCounter > frames)
		runCounter = 0.0f;
	shader.setUniform1f("u_xTextureOffset", (((int)runCounter)) * xTexStride);
}

void Game::update_fruit(Fruit& fruit, VertexArray& fruit_vao, float& frame, float textureSlot)
{
	
	if (!fruit.is_collected())
	{
		staticViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(fruit.getX() + level_displacement, fruit.getY(), 0.0f));
		shader.setUniform1f("facing_right", 1.0f);
		if (Physics::is_collision_player_fruit(player, fruit))
			fruit.collect();
		if (!fruit.is_collected())
		{
			MVP_Scene = glm::mat4(1.0f) * proj * (staticViewMatrix);
			shader.setUniform1f("currentTex", textureSlot);
			shader.setUniformMat4f("u_MVP", MVP_Scene);
			do_fruit_animation(14, frame, 0.588352f);
			renderer.draw(fruit_vao, shader);
		}
	}

}
void Game::do_fruit_animation(int frames, float& counter, float xTextureStride)
{
	shader.setUniform1f("u_xInverseOffset", 0.0f);
	counter += dt * 0.9f;
	shader.setUniform1f("u_yTextureOffset", 0.0f);
	if ((int)counter > frames)
		counter = -5.0f;
	shader.setUniform1f("u_xTextureOffset", (float)((int)counter) * xTextureStride);
}

void Game::update_angry_block(AngryBlock& angryBlock, VertexArray& ablock_vao, float& frame)
{
	angryBlock.update_timer(dt);
	
	shader.setUniform1f("u_yTextureOffset", 0.0f);
	shader.setUniform1f("u_xInverseOffset", 0.0f);
	shader.setUniform1f("facing_right", 1.0f);
	shader.setUniform1f("currentTex", 6.0f);
	angryBlock.moveY(dt);
	update_ablock_animations(5, angryBlock.get_blink_frame(), 0.0f);
	playerView = glm::translate(glm::mat4(1.0f), glm::vec3(angryBlock.getX() + level_displacement, angryBlock.getY(), 0.0f));
	MVP_Scene = model * proj * playerView;
	shader.setUniformMat4f("u_MVP", MVP_Scene);
	renderer.draw(ablock_vao, shader);
}
void Game::update_ablock_animations(int frames, float& counter, float xTextureStride)
{

	shader.setUniform1f("u_xTextureOffset", (float)(int)counter * (0.15238 + 0.04761));

}

// Old Stuff
void Game::init_player_textures(float offset)
{
	// ------------------ Idle Texture ------------------------ \\ .
	//for (int i = 0; i < 10; i++)
	//{
	//	std::string s = std::to_string(i);
	//	frames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Idle/Idle0" + s + ".png")));
	//}
	//frames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Idle/Idle10.png")));
	//
	//for (auto& ptr : frames){
	//	ptr->init();
	//	ptr->setVertAttribs(1, 2, 5, 3);
	//}
	//
	//// ------------------ Running Texture ------------------------ \\ .
	//for (int i = 0; i < 10; i++)
	//{
	//	std::string s = std::to_string(i);
	//	runningFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Run/running0" + s + ".png")));
	//}
	//runningFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Run/running10.png")));
	//runningFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Run/running11.png")));
	//
	//for (auto& ptr : runningFrames) {
	//	ptr->init();
	//	ptr->setVertAttribs(1, 2, 5, 3);
	//}
	//
	//// ----------------- In Air Texture -------------------------- \\ .
	//airFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Jump.png")));
	//airFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Fall.png")));
	//for (auto& ptr : airFrames) {
	//	ptr->init();
	//	ptr->setVertAttribs(1, 2, 5, 3);
	//}


}
void Game::init_enemy_texture(VertexArray& enemy_vao, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkVector, std::vector<std::unique_ptr<Texture>>& runningVector, unsigned int idleFrames, unsigned int walkFrames, unsigned int runningFrames, const std::string& idlePath, const std::string& walkPath, const std::string& runningPath)
{
	// --------------------------------- Idle Texture -------------------------------------------- \\ .
	if (idleFrames > 10) {
		unsigned int difference = idleFrames - 10;
		for (int i = 0; i < 10; i++)
		{
			std::string s = std::to_string(i);
			idleVector.push_back(std::move(std::make_unique<Texture>(idlePath + "0" + s + ".png")));
		}
		for (int i = 10; i < 10 + difference; i++)
		{
			std::string s = std::to_string(i);
			idleVector.push_back(std::move(std::make_unique<Texture>(idlePath + s + ".png")));
		}
	}
	else {
		for (int i = 0; i < idleFrames; i++)
		{
			std::string s = std::to_string(i);
			idleVector.push_back(std::move(std::make_unique<Texture>(idlePath + "0" + s + ".png")));
		}
	}
	for (auto& ptr : idleVector) {
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}


	// --------------------------------- Walking Texture -------------------------------------------- \\ .
	if (walkFrames > 10) {
		unsigned int difference = walkFrames - 10;
		for (int i = 0; i < 10; i++)
		{
			std::string s = std::to_string(i);
			walkVector.push_back(std::move(std::make_unique<Texture>(walkPath + "0" + s + ".png")));
		}
		for (int i = 10; i < 10 + difference; i++)
		{
			std::string s = std::to_string(i);
			walkVector.push_back(std::move(std::make_unique<Texture>(walkPath + s + ".png")));
		}
	}
	else {
		for (int i = 0; i < walkFrames; i++)
		{
			std::string s = std::to_string(i);
			walkVector.push_back(std::move(std::make_unique<Texture>(walkPath + "0" + s + ".png")));
		}
	}
	for (auto& ptr : walkVector) {
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}

	// --------------------------------- Running Texture -------------------------------------------- \\ .
	if (runningFrames > 10) {
		unsigned int difference = runningFrames - 10;
		for (int i = 0; i < 10; i++)
		{
			std::string s = std::to_string(i);
			runningVector.push_back(std::move(std::make_unique<Texture>(runningPath + "0" + s + ".png")));
		}
		for (int i = 10; i < 10 + difference; i++)
		{
			std::string s = std::to_string(i);
			runningVector.push_back(std::move(std::make_unique<Texture>(runningPath + s + ".png")));
		}
	}
	else {
		for (int i = 0; i < runningFrames; i++)
		{
			std::string s = std::to_string(i);
			runningVector.push_back(std::move(std::make_unique<Texture>(runningPath + "0" + s + ".png")));
		}
	}
	for (auto& ptr : runningVector) {
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}
}
void Game::init_fruit_texture(VertexArray& fruit_vao, std::vector<std::unique_ptr<Texture>>& fruitVector, unsigned int spriteCount, const std::string& path)
{
	if (spriteCount > 10) {
		unsigned int difference = spriteCount - 10;
		for (int i = 0; i < 10; i++)
		{
			std::string s = std::to_string(i);
			fruitVector.push_back(std::move(std::make_unique<Texture>(path + "0" + s + ".png")));
		}
		for (int i = 10; i < 10 + difference; i++)
		{
			std::string s = std::to_string(i);
			fruitVector.push_back(std::move(std::make_unique<Texture>(path + s + ".png")));
		}
	}
	else {
		for (int i = 0; i < spriteCount; i++)
		{
			std::string s = std::to_string(i);
			fruitVector.push_back(std::move(std::make_unique<Texture>(path + "0" + s + ".png")));
		}
	}
	for (auto& ptr : fruitVector) {
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}
}
void Game::init_vertices(Entity& entity, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height)
{
	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, x, y, entity.getWidth(), entity.getHeight(), tex_left, tex_bottom, tex_width, tex_height);
	e_VAO.init(vert, 20, indices, 6);
	e_VAO.setVertexAttribPointersf(0, 3, 5, 0);
	// VAO Layout location
	// 3 coordinates, so size of 3 per attributes
	// Total of 5 values (plus the texture) so 5 as stride
	// 0 Offset to begn vertex coords
}
void Game::init_vertices(Fruit& fruit, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_bottom, float tex_width, float tex_height)
{
	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, x, y, fruit.getWidth(), fruit.getHeight(), tex_left, tex_bottom, tex_width, tex_height);
	e_VAO.init(vert, 20, indices, 6);
	e_VAO.setVertexAttribPointersf(0, 3, 5, 0);
};
void Game::buffer_next_frame(VertexArray& vao, Texture& texture, float(&vert)[20], float space)
{

	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, 0, 0, 64.0f, 64.0f, 0.0f, 0.0f, space, 0.5f);
	vao.setVertexAttribPointersf(0, 3, 5, 0);
	texture.setVertAttribs(1, 2, 5, 3);
}
void Game::do_pig_animations(Pig& p, std::vector<std::unique_ptr<Texture>>& idleVector, std::vector<std::unique_ptr<Texture>>& walkVector, std::vector<std::unique_ptr<Texture>>& runningVector, float& currentFrame)
{
	currentFrame += dt * 2;
	if (p.is_enraged())
	{
		if (currentFrame > (float)(runningVector.size() - 1) + 0.5f)
			currentFrame = 0.0f;
		// Invert texture depending on velocity (negative means moving left, positive means moving right) For pig Texture, default is facing left, so values are switched
		if (p.getXVelocity() > 0)
			shader.setUniform1f("facing_right", 0.0f);
		else if (p.getXVelocity() < 0) 
			shader.setUniform1f("facing_right", 1.0f);
		runningVector[(int)currentFrame]->bind();
	}
	else
	{
		if (currentFrame > (float)(walkVector.size() - 1) + 0.5f)
			currentFrame = 0.0f;
		if (p.getXVelocity() > 0)
			shader.setUniform1f("facing_right", 0.0f);
		else if (p.getXVelocity() < 0)
			shader.setUniform1f("facing_right", 1.0f);
		walkVector[(int)currentFrame]->bind();
	}
	if (p.getXVelocity() == 0)
	{
		if (currentFrame > (float)(idleVector.size() - 0.2f))
			currentFrame = 0.0f;
		idleVector[(int)currentFrame]->bind();
	}
}
void Game::do_fruit_animatinos(Fruit& fruit, std::vector<std::unique_ptr<Texture>>& frames, float& currentFrame)
{
	currentFrame += dt * 2;
	if (currentFrame > frames.size() - 0.5f)
		currentFrame = 0.0f;
	frames[(int)currentFrame]->bind();
}
void Game::update_texture_frame(float& variable, float dt, float max)
{
	variable += dt * 1.5f;
	if (variable >= max)
		variable = 0;
}
void Game::update_dt()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	this->dt = (this->currentTime - this->lastTime) * 10;
	if (this->dt > 0.07)
		this->dt = 0.07;
	this->lastTime = currentTime;
	
}

Game::~Game()
{
	std::cout << "Destroy" << std::endl;
}