#include "Game.h"
#include <iostream>
#include <iomanip>
#define WIDNOW_WIDTH = 1024.0F
#define WINDOW_HEIGHT = 768.0F
Game::Game()
	:
	wrapper(), player(playerStartingCoords.x, playerStartingCoords.y, 64.0f, 64.0f),
	VAO(), hitbox(playerStartingCoords.x + 5.0f, playerStartingCoords.y + 5.0f, 44.0f, 44.0f),
	pig(pigCoords.x, pigCoords.y, 96.0f, 80.0f),
	window(screenWidth, screenHeight, "OpenGl Game"),
	texture("Assets/Background/Green.png"),
	texture2("Assets/Tiles/GrassTile.png"),
	model(1.0f), view(1.0f), proj(1.0f),
	MVP_Scene(1.0f), MVP_Player(1.0f), 
	playerModel(1.0f), playerView(1.0f),
	pigView(1.0f)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	init_vertices(player, VAO, tileVert, 0.0f, 704.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	// Player Stuff
	init_vertices(player, VAOPlayer, playerVert, 0.0f, 0.0f, 0.125f, 0.0f, 0.75f, 0.875f);
	init_player_textures();

	init_vertices(pig, VAOPig, pigVert, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	init_enemy_texture(VAOPig, pigIdle, pigWalk, pigRunning, 10, 16, 12, "Assets/Enemies/AngryPig/Idle/Idle", "Assets/Enemies/AngryPig/Walk/Walk", "Assets/Enemies/AngryPig/Run/Run");

	MVP_Player = playerModel * proj * playerView;
	playerView = glm::translate(glm::mat4(1.0f), glm::vec3(playerScreenX, playerScreenY, 0.0f));
	
	pigView = glm::translate(glm::mat4(1.0f), glm::vec3(pig.getX(), pig.getY(), 0.0f));

	proj = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
	view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
	
	MVP_Scene = model * proj * view;
	MVP_Player = playerModel * proj * playerView;
	board = level.get_board();
	playerMiddle = (playerScreenX + playerScreenX + player.getWidth()) / 2;
	
}

void Game::run()
{
	
	composeFrame();

	while (gameRunning)
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
		ImGui::Text("Tile: (%.2f, %.2f)", level.get_grass_blocks()[0].getX(), level.get_grass_blocks()[0].getY());
		ImGui::Text("Tile Displacement: %.2f", level.get_tile_displacement_x());
		ImGui::Text("Player is moving: %d$", player.is_moving());
		ImGui::Text("Player Screen Coords: (%.2f, %.2f)", playerScreenX, playerScreenY);
		ImGui::Text("Bounds: (%.2f, %.2f)", leftBound, rightBound);
		ImGui::Text("pCenter = %.2f", playerMiddle);
		ImGui::Text("Pig = (%.2f, %.2f)", pig.getX(), pig.getY());
		ImGui::Text("Collision: %d", Physics::is_collision_player_entity(player, pig));
		ImGui::End();	
		// <---------------- Rendering Code --------------------> \\

		shader.setUniformMat4f("u_MVP", MVP_Scene);
		shader.setUniform1f("facing_right", 1.0f);
		shader.setUniform1f("player_being_rendered", 0.0f);
		if (drawTriangle)
		{
			for (int r = 0; r < level.get_rows(); r++)
			{
				for (int c = 0; c < level.get_columns(); c++)
				{
					view = glm::translate(model, glm::vec3(level.get_tile_displacement_x() + (64 * c), -(64 * r), 0.0f));
					MVP_Scene = model * proj * view;
					shader.setUniformMat4f("u_MVP", MVP_Scene);

					if (board[c + (r * level.get_columns())] == level.get_grass_tile())
					{
						texture2.bind(); // Bind grass block tile
					}
					if (board[c + (r * level.get_columns())] == level.get_background_tile())
					{
						texture.bind();	// Bind background texture
					}

					renderer.draw(VAO, shader);

				}
			}
		}
		
		// <================ Enemy Stuff =================> \\
		
		if (!pig.is_enraged())
			do_player_entity_collisions();
		do_pig_animations(pig, pigIdle, pigWalk, pigRunning, pigCurrentFrame);
		pig.move(dt);
		pigView = glm::translate(model, glm::vec3(pig.getX() + level.get_tile_displacement_x(), pig.getY(), 0.0f));
		MVP_Scene = model * proj * pigView;
		shader.setUniformMat4f("u_MVP", MVP_Scene);
		//update_texture_frame(pigCurrentFrame, dt, 9);
		//pigIdle[pigCurrentIdleFrame]->bind();
		renderer.draw(VAOPig, shader);

		// <================ Player Frames Stuff =================> \\

		shader.setUniform1f("player_being_rendered", 1.0f);
		if (glfwGetKey(window.getWindow(), GLFW_KEY_B) == GLFW_PRESS)
			shader.setUniform1f("facing_right", 0.0f);
		if (glfwGetKey(window.getWindow(), GLFW_KEY_R) == GLFW_PRESS)
			shader.setUniform1f("facing_right", 1.0f);
		playerView = glm::translate(playerModel, glm::vec3(playerScreenX, player.getY(), 0.0f));

		player.moveX(dt);
		do_x_collisions();
		player.moveY(dt);
		do_y_collisions();


		MVP_Player = playerModel * proj * playerView;
		processInput();
		
		shader.setUniformMat4f("u_MVP", MVP_Player);
		
		// Update the frame every time.
		update_texture_frame(idleFrame, dt, 10);
		update_texture_frame(runningFrame, dt, 11);

		renderer.draw(VAOPlayer, shader);
		//do_collisions();
		playerMiddle = (playerScreenX + playerScreenX + player.getWidth()) / 2;
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Switch buffers lol
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
		// ---------------- Testing Code -------------------- \\
		
		update_dt();
		std::cout << std::fixed;
		std::cout << std::setprecision(2);
		
		currentX = player.getX();
		displacement = currentX - lastX;
		lastX = currentX;

		currentTileX = level.get_grass_blocks()[0].getX();
		tileDisplacement = level.get_grass_blocks()[0].getX() - lstTileX;
		lstTileX = currentTileX;
		
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Game::processInput()
{
	
	if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		gameRunning = false;
	}

	// Left Movement
	if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		facing_right = false;
		runningFrames[runningFrame]->bind();
		player.set_moving_right_state(false);
		player.set_moving_left_state(true);
		if (player.can_move_left())
		{
			if (playerMiddle < leftBound && level.get_tile_displacement_x() <= 0)
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
		runningFrames[runningFrame]->bind();
		player.set_moving_left_state(false);
		player.set_moving_right_state(true);
		if (player.can_move_right())
		{
			if (playerMiddle > rightBound && level.get_tile_displacement_x() >= -256)
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
		frames[idleFrame]->bind();
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
		airFrames[1]->bind();
	}
	if (facing_right) shader.setUniform1f("facing_right", 1.0f);
	else shader.setUniform1f("facing_right", 0.0f);
	if (player.is_jumping()) airFrames[0]->bind();
	
}  

void Game::composeFrame()
{
	VAO.bufferVertexData(20, tileVert);
	texture.init();
	texture.setVertAttribs(1, 2, 5, 3);
	texture2.init();
	texture2.setVertAttribs(1, 2, 5, 3);


	std::string vertSource;
	std::string fragSource;
	// Read the contents of the shaders into our strings
	shader.readShaderFile("Shaders/Vertex.vert", vertSource);
	shader.readShaderFile("Shaders/Fragment.frag", fragSource);

	// std::cout << vertSource << fragSource << std::endl;
	// Initialize our shader by passing the source code
	shader.initShaders(vertSource, fragSource);
	
	// Finally, use our shader program
	shader.use();
	
	
	MVP_Scene = model * proj * view;
	// <-------------------- Uniform Stuff ------------------------> \\
	
	//shader.setUniform1i("u_Texture", 0);
	shader.setUniform1f("facing_right", 1.0f);
	shader.setUniformMat4f("u_MVP", MVP_Scene);
	level.init_grass_tiles(768.0f);
} 
void Game::init_player_textures()
{
	// ------------------ Idle Texture ------------------------ \\ .
	for (int i = 0; i < 10; i++)
	{
		std::string s = std::to_string(i);
		frames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Idle/Idle0" + s + ".png")));
	}
	frames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Idle/Idle10.png")));

	for (auto& ptr : frames){
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}

	// ------------------ Running Texture ------------------------ \\ .
	for (int i = 0; i < 10; i++)
	{
		std::string s = std::to_string(i);
		runningFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Run/running0" + s + ".png")));
	}
	runningFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Run/running10.png")));
	runningFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Run/running11.png")));

	for (auto& ptr : runningFrames) {
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}

	// ----------------- In Air Texture -------------------------- \\ .
	airFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Jump.png")));
	airFrames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Fall.png")));
	for (auto& ptr : airFrames) {
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}
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
void Game::init_vertices(Entity& entity, VertexArray& e_VAO, float(&vert)[20], float x, float y, float tex_left, float tex_right, float tex_width, float tex_height)
{
	zArrayConverter::convert_coordinates_to_vert_tex_array_reference(vert, x, y, entity.getWidth(), entity.getHeight(), tex_left, tex_right, tex_width, tex_height);
	e_VAO.init(vert, 20, indices, 6);
	e_VAO.setVertexAttribPointersf(0, 3, 5, 0);
	// VAO Layout location
	// 3 coordinates, so size of 3 per attributes
	// Total of 5 values (plus the texture) so 5 as stride
	// 0 Offset to begn vertex coords
}
void Game::do_player_entity_collisions()
{
	if (Physics::is_collision_player_entity(player, pig))
		pig.enrage();
}
void Game::do_x_collisions()
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
		//if (Physics::is_collision_player_tile(player, tile) && player.is_moving_left())
		//{
		//	player.setX(player.getX() + 0.1f);
		//	playerScreenX = playerScreenX + 0.1f;
		//}
		//if (Physics::is_collision_player_tile(player, tile) && player.is_moving_right())
		//{
		//	player.setX(player.getX() - 1.0f);
		//	playerScreenX = playerScreenX - 1.0f;
		//}
		if (Physics::is_collision_player_tile(player, tile) && player.is_moving_left())
		{
			//updatePastX = false;
			//player.set_can_move_left(false);
			player.setX(player.getX() + (tile.getX() + tile.getWidth() - player.getX()));
			playerScreenX = playerScreenX + (tile.getX() + level.get_tile_displacement_x() + tile.getWidth() - playerScreenX);
			//player.setX(pastX);
			//playerScreenX = pastX;
		}
		
		if (Physics::is_collision_player_tile(player, tile) && player.is_moving_right())
		{
			player.setX(player.getX() - (player.getX() + player.getWidth() - tile.getX()));
			playerScreenX = playerScreenX - (playerScreenX + player.getWidth() - tile.getX() - level.get_tile_displacement_x());
			//playerScreenX = 
		}
	}
	player.applyGravity(dt);
}
void Game::do_y_collisions()
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
}
void Game::update_texture_frame(float& variable, float dt, float max)
{
	variable += dt * 1.5;
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