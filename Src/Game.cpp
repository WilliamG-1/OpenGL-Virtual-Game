#include "Game.h"
#include <iostream>
#define WIDNOW_WIDTH = 1024.0F
#define WINDOW_HEIGHT = 768.0F
Game::Game()
	:
	wrapper(), player(playerStartingCoords.x, playerStartingCoords.y, 64.0f, 64.0f),
	VAO(), // VAOPlayer(),
	window(1024, 768, "OpenGl Game"),
	texture("Assets/Background/Green.png"),
	texture2("Assets/Tiles/GrassTile.png"),
	playerTex("Assets/Virtual Guy/Idle/Idle00.png"),
	model(1.0f), view(1.0f), proj(1.0f),
	MVP_Scene(1.0f), MVP_Player(1.0f), 
	playerModel(1.0f), playerView(1.0f)
{
	
	//idleAnimation.push_back(Texture("Assets/Virtual Guy/Idle/Idle10.png"));
	
	unsigned int indices[6] = {
		0, 1, 2,  2, 3, 0
	};
	unsigned int indices2[6] = {
		0, 1, 2,  2, 3, 0
	};
	//VAO.init(wrapper, siz eof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
	float a[20];
	//tileVert = zArrayConverter::convert_coordinates_to_vert_tex_array(a, backgroundTile.getX(), backgroundTile.getY(), backgroundTile.getWidth(), backgroundTile.getHeight(), 0.0f, 0.0f, 1.0f, 1.0f);
	tileVert = zArrayConverter::convert_coordinates_to_vert_tex_array(a, 0.0f, 704.0f, 64.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	VAO.init(tileVert, 20, indices, sizeof(indices) / sizeof(unsigned int));
	// VAO Layout location
	// 3 coordinates, so size of 3 per attributes
	// Total of 5 values (plus the texture) so 5 as stride
	// 0 Offset to begn vertex coords
	VAO.setVertexAttribPointersf(0, 3, 5, 0);

	//  Player Stuff
	float b[20];
	playerVert = zArrayConverter::convert_coordinates_to_vert_tex_array(b, player.getX(), player.getY(), player.getWidth(), player.getHeight(), 0.125f, 0.0f, 0.75f, 0.825f);

	VAOPlayer.init(playerVert, 20, indices2, sizeof(indices2) / sizeof(unsigned int));
	VAOPlayer.setVertexAttribPointersf(0, 3, 5, 0);

	//playerView = glm::translate(playerModel, glm::vec3(0-player.getX(), 0-player.getY(), 0.0f));
	MVP_Player = playerModel * proj * playerView;

	playerTex.init();
	playerTex.setVertAttribs(1, 2, 5, 3);
	
	for (int i = 0; i < 9; i++)
	{
		std::string s = std::to_string(i);
		frames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Idle/Idle0" + s + ".png")));
	}
	frames.push_back(std::move(std::make_unique<Texture>("Assets/Virtual Guy/Idle/Idle10.png")));

	for (auto& ptr : frames)
	{
		ptr->init();
		ptr->setVertAttribs(1, 2, 5, 3);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
	view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
	
	MVP_Scene = model * proj * view;
	MVP_Player = playerModel * proj * playerView;
	board = level.get_board();

	for (int r = 0; r < level.get_rows(); r++)
	{
		for (int c = 0; c < level.get_columns(); c++)
		{
			if (board[c + (r * level.get_columns())] == 'X')
			{
				grassTiles.push_back(std::move(std::make_unique<Tile>(c * 64, 704.0f -(r * 64), 64.0f, 64.0f)));
			}

		}
	}

	for (auto& u_ptr : grassTiles)
		std::cout << "Tile x :" << u_ptr->getX() << ", Tile y: " << u_ptr->getY() << std::endl;
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
		ImGui::Text("Selection Screen OmegaLol");
		ImGui::Checkbox("Draw Triangle", &drawTriangle);
		ImGui::SliderFloat("Move Left & Right", &leftRightMove, -960.0f, 960.0f);


		ImGui::End();	
		// <---------------- Rendering Code --------------------> \\
		
		//view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
		//for (auto& p : grassTiles)
		//{
		//	p->setX((leftRightMove));
		//}
		shader.setUniformMat4f("u_MVP", MVP_Scene);
		
		if (drawTriangle)
		{
			for (int r = 0; r < level.get_rows(); r++)
			{
				for (int c = 0; c < level.get_columns(); c++)
				{
					view = glm::translate(model, glm::vec3(leftRightMove + (64 * c), -(64 * r), 0.0f));
					MVP_Scene = model * proj * view;
					shader.setUniformMat4f("u_MVP", MVP_Scene);

					if (board[c + (r * level.get_columns())] == 'X')
					{
						texture2.bind();
					}
					if (board[c + (r * level.get_columns())] == '0')
					{
						texture.bind();
					}

					renderer.draw(VAO, shader);

				}
			}
		}

		// <================ Player Frames Stuff =================> \\

		MVP_Player = playerModel * proj * playerView;

		playerView = glm::translate(playerModel, glm::vec3(player.getX()-playerStartingCoords.x, player.getY() - playerStartingCoords.y, 0.0f));
		player.moveY(dt);

		MVP_Player = playerModel * proj * playerView;
		
		shader.setUniformMat4f("u_MVP", MVP_Player);
		frames[currentFrame]->bind();
		// Update the frame every time.
		currentFrame += 0.115f;
		if (currentFrame > 9.9)
			currentFrame = 0.0f;

		renderer.draw(VAOPlayer, shader);
		// <================ Player Frames Stuff =================> \\
		

		if (currentFrame == .115f)
		{
			//std::cout << " NO collision" << std::endl;
			//std::cout << "Player X: " << player.getX() << ", Player Y: " << player.getY() << std::endl;
			std::cout << "Tile x: " << grassTiles[0]->getX() << ", Tile y:" << grassTiles[0]->getY() << std::endl;
		}
		
		
		for (auto& ptr : grassTiles)
		{
			if (Physics::is_collision_player_tile(player, *ptr) && player.is_falling())
			{
				player.set_can_jump(true);
				player.set_moving_up_state(false);
				player.set_can_move_down(false);
				int pos = player.getY() + 64.0f;
				pos = pos - pos % 64;
				player.setY(pos);
			}
			//else if (Physics::is_collision_player_tile(player, *ptr) && player.getVy() > 0)
			//{
			//	int pos = player.getY();
			//	player.setY(player.getY() - (pos % 64));
			//}

			if (Physics::is_collision_player_tile(player, *ptr) && player.is_moving_right())
			{
				//int pos = player.getX();
				//player.setX(player.getX() - (pos % 64 + player.getVx() * dt));
				player.setX(ptr->getX() - 64.0f);
			}
			else if (Physics::is_collision_player_tile(player, *ptr) && player.is_moving_left())
			{
				//int pos = player.getX() + 64.0f;
				//pos = pos - pos % 64 + 5.0f;
				player.setX(ptr->getX() + 64.0f + player.getVy() * dt);
			}
			

		}
		player.applyGravity(dt);
		//if (player.can_move_down())
		
		
		// <================ Player Frames Stuff =================> \\

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Switch buffers lol
		glfwSwapBuffers(window.getWindow());
		glfwPollEvents();
		// ---------------- Changing Code -------------------- \\
		
		updateDT();
		processInput();

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
	if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS && player.can_move_left())
	{
		player.setVx(30);
		player.moveX(-1, dt);
		player.set_moving_left_state(true);
	}
	// Right Movement
	else if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS && player.can_move_right())
	{
		player.setVx(30);
		player.moveX(1, dt);
		player.set_moving_right_state(true);
	}
	else
		player.setVx(0);

	// Jumping
	if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && player.can_move_up())
	{
		player.jump(dt);
		player.set_can_jump(false);
		player.set_moving_up_state(true);
		player.set_can_move_down(true);
	}

	if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_RELEASE)
	{
		player.set_moving_left_state(false);
		player.set_can_move_left(true);
	}
	if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_RELEASE)
	{
		player.set_moving_right_state(false);
		player.set_can_move_right(true);	
	}
	


	
}  

void Game::composeFrame()
{
	VAO.bufferVertexData(20, vertices);
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
	shader.setUniformMat4f("u_MVP", MVP_Scene);
} 

void Game::updateDT()
{
	this->currentTime = static_cast<float>(glfwGetTime());
	this->dt = (this->currentTime - this->lastTime) * 10;
	if (this->dt > 0.07)
		this->dt = 0.07;
	this->lastTime = currentTime;
	
}

//template <typename T>
//void Game::copyArrToStruct(struct Arrays& A, T data[], unsigned int size, ArrayType type)
//{
//	ArrayType t = type;
//	if (type == ArrayType::VERTEX)
//	{
//		for (unsigned int i = 0; i < size; i++)
//		{
//			A.vertices[i] = data[i];
//		}
//	}
//	else if (type == ArrayType::ELEMENT)
//	{
//		for (unsigned int i = 0; i < size; i++)
//		{
//			A.indices[i] = data[i];
//		}
//	}
//}

Game::~Game()
{
	std::cout << "Destroy" << std::endl;
}