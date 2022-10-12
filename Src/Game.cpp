#include "Game.h"
#include <iostream>
#define WIDNOW_WIDTH = 1024.0F
#define WINDOW_HEIGHT = 768.0F
Game::Game()
	:
	wrapper(), player(128.0f, 500.0f, 32.0f, 64.0f),
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
	playerVert = zArrayConverter::convert_coordinates_to_vert_tex_array(b, 0.0f, 0.0f, 64.0f, 64.0f, 0.125f, 0.0f, 0.75f, 0.825f );

	VAOPlayer.init(playerVert, 20, indices2, sizeof(indices2) / sizeof(unsigned int));
	VAOPlayer.setVertexAttribPointersf(0, 3, 5, 0);
	
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

	
	
	//for (int i = 0; i < 9; i++)
	//{
	//	// Convert integer to string
	//	std::string num = std::to_string(i);
	//	std::cout << "The number is: " << num << std::endl;
	//	Texture texture("Assets/Virtual Guy/Idle/Idle01.png");
	//	//texture.init();
	//	//texture.setVertAttribs(1, 2, 5, 3);
	//	idleAnimation[i] = std::move(texture);
	//
	//}
	//for (Texture& t : idleAnimation)
	//{
	//	t.init();
	//	t.setVertAttribs(1, 2, 5, 3);
	//}
	//idleAnimation[9] = playerTex;
	//idleAnimation[4] = playerTex;
		
	//playerTex.init();
	//playerTex.setVertAttribs(1, 2, 5, 3);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);

	view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));

	playerView = glm::translate(model, glm::vec3(player.getX(), player.getY(), 0.0f));
	
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
	for (int i = 0; i < 20; i++)
	{
		std::cout << vertices[i] << std::endl;
	}
	for (int i = 0; i < 20; i++)
	{
		std::cout << tileVert[i] << std::endl;
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

		processInput();
		// Clear Screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		// ========================= ImGui ==============================
		ImGui::Begin("Window");
		ImGui::Text("Selection Screen OmegaLol");
		ImGui::Checkbox("Draw Triangle", &drawTriangle);
		ImGui::SliderFloat("Move Left & Right", &leftRightMove, 960.0f, -960.0f);


		ImGui::End();	
		// <---------------- Rendering Code --------------------> \\

		
		view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
		

		shader.setUniformMat4f("u_MVP", MVP_Scene);
		
		if (drawTriangle)
		{
			bool drawBackground = true;
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
		
		playerView = glm::translate(playerModel, glm::vec3(player.getX(), player.getY(), 0.0f));
		MVP_Player = playerModel * proj * playerView;
		
		shader.setUniformMat4f("u_MVP", MVP_Player);
		frames[currentFrame]->bind();
		// Update the frame every time.
		currentFrame += 0.115f;
		if (currentFrame > 9.9)
			currentFrame = 0.0f;
		renderer.draw(VAOPlayer, shader);
		if (currentFrame == .115f)
			std::cout << " NO collision" << std::endl;
		
		//std::cout << "Player x: " << player.getX() << "Player y: " << player.getY() << std::endl;
		//if (!player.is_moving())
		//	std::cout << "Player standing still!" << std::endl;
		//else {
		//	if (player.is_moving_right())
		//		std::cout << "Moving Right" << std::endl;
		//	if (player.is_moving_left())
		//		std::cout << "Moving Left" << std::endl;
		//	if (player.is_jumping())
		//		std::cout << "Player \"Jumping\"" << std::endl;
		//	if (player.is_falling())
		//		std::cout << "Player is \"Falling\"" << std::endl;
		//}
		//
		for (auto& ptr : grassTiles)
		{
			if (Physics::entity_left_collide_right_tile(player, *ptr))
				std::cout << "Collision from left to right!" << std::endl;
			//if (Physics::entity_right_collide_left_tile(player, *ptr))
			//	std::cout << "Collision from right to left!" << std::endl;
			//if (Physics::entity_top_collide_bottom_tile(player, *ptr))
			//	std::cout << "Collision from top to bottom!" << std::endl;
			//if (Physics::entity_bottom_collide_top_tile(player, *ptr))
			//	std::cout << "Collision from bottom to top!" << std::endl;
		}
		
		
		// <================ Player Frames Stuff =================> \\

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Switch buffers lol
		glfwSwapBuffers(window.getWindow());

		// ---------------- Changing Code -------------------- \\
		
		//leftRightMove -= 1.0f;
		//if (leftRightMove <= -(level.get_columns() * 32) + 100)
			//leftRightMove = 0;

		


	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void Game::processInput()
{
	glfwPollEvents();
	if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		gameRunning = false;
	}
	if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		player.moveX(-1.0f);
	}
	else if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		player.moveX(1.0f);
	}
	else player.moveX(0);

	if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		player.moveY(1.0f);
	}
	else if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		player.moveY(-1.0f);
	}
	else player.moveY(0);
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

	std::cout << vertSource << fragSource << std::endl;
	// Initialize our shader by passing the source code
	shader.initShaders(vertSource, fragSource);
	
	// Finally, use our shader program
	shader.use();
	
	
	MVP_Scene = model * proj * view;
	// <-------------------- Uniform Stuff ------------------------> \\
	
	//shader.setUniform1i("u_Texture", 0);
	shader.setUniformMat4f("u_MVP", MVP_Scene);
} 

template <typename T>
void Game::copyArrToStruct(struct Arrays& A, T data[], unsigned int size, ArrayType type)
{
	ArrayType t = type;
	if (type == ArrayType::VERTEX)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			A.vertices[i] = data[i];
		}
	}
	else if (type == ArrayType::ELEMENT)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			A.indices[i] = data[i];
		}
	}
}

Game::~Game()
{
	std::cout << "Destroy" << std::endl;
}