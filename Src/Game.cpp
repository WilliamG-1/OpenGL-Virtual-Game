#include "Game.h"
#include <iostream>

Game::Game()
	:
	wrapper(), //wrapper2(),
	VAO(), //VAO2(),
	window(1024, 768, "OpenGl Game"),
	texture("Assets/Background/Blue.png"),
	texture2("Assets/Tiles/GrassTile.png"),
	model(1.0f), view(1.0f), proj(1.0f)
{
	// Copies 
	//copyArrToStruct<float>(wrapper, vertices, 40, ArrayType::VERTEX);
	//copyArrToStruct<unsigned int>(wrapper, indices, 12, ArrayType::ELEMENT);

	float vertices[20] = {
		// Vertex Coords			Texture Coords
		000.0f, 704.0f, 0.0f,		0.0f, 0.0f,		// Bottom Left  (0)
		064.0f, 704.0f, 0.0f,		1.0f, 0.0f,     // Bottom Right (1)
		064.0f, 768.0f, 0.0f,		1.0f, 1.0f,     // Top Right    (2)
		000.0f, 768.0f, 0.0f,		0.0f, 1.0f		// Top Left     (3)
	};

	unsigned int indices[6] = {
		0, 1, 2,  2, 3, 0
	};
	//VAO.init(wrapper, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
	VAO.init(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));

	// VAO Layout location
	// 3 coordinates, so size of 3 per attributes
	// Total of 5 values (plus the texture) so 5 as stride
	// 0 Offset to begn vertex coords

	VAO.setVertexAttribPointersf(0, 3, 5, 0);
	//VAO2.init(wrapper2, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
	//VAO.setVertexAttribPointersf(0, 3, 5, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f);
	//proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
	model = glm::mat4(1.0f);
	board = level.get_board();
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
		ImGui::SliderFloat("Move Left & Right", &leftRightMove, 0.0f, 960.0f);


		ImGui::End();	
		// <---------------- Rendering Code --------------------> \\

		
		view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
		glm::mat4 MVP = model * proj * view;

		shader.setUniformMat4f("u_MVP", MVP);
		
		if (drawTriangle)
		{
			bool drawBackground = true;
			for (int r = 0; r < level.get_rows(); r++)
			{
				for (int c = 0; c < level.get_columns(); c++)
				{
					view = glm::translate(model, glm::vec3(leftRightMove + (64 * c), -(64 * r), 0.0f));
					MVP = model * proj * view;
					shader.setUniformMat4f("u_MVP", MVP);

					if (board[c + (r * level.get_columns())] == 'X')
					{
						texture2.setVertAttribs(1, 2, 5, 3);
						texture2.bind();
						shader.use();
						drawBackground = false;
					}
					if (board[c + (r * level.get_columns())] == '0')
					{
						texture.setVertAttribs(1, 2, 5, 3);
						texture.bind();
						shader.use();
						drawBackground = false;
					}
					
					renderer.draw(VAO, shader);
				}
			}
		}
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Switch buffers lol
		glfwSwapBuffers(window.getWindow());

		// ---------------- Changing Code -------------------- \\
		

		


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
}  

void Game::composeFrame()
{
	
	glm::mat4 MVP = model * proj * view;


	texture.init();
	texture.setVertAttribs(1, 2, 5, 3);
	texture2.init();

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


	texture.bind();
	
	
	MVP = model * proj * view;
	// <-------------------- Uniform Stuff ------------------------> \\
	

	shader.setUniform1i("u_Texture", 0);
	shader.setUniformMat4f("u_MVP", MVP);
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