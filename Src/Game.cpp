#include "Game.h"
#include <iostream>

Game::Game()
	:
	wrapper(), //wrapper2(),
	VAO(), //VAO2(),
	window(800, 600, "OpenGl Game"),
	texture("Assets/Heart.png"),
	model(1.0f), view(1.0f), proj(1.0f)
{
	// Copies 
	copyArrToStruct<float>(wrapper, vertices, 20, ArrayType::VERTEX);
	copyArrToStruct<unsigned int>(wrapper, indices, 6, ArrayType::ELEMENT);
	
	VAO.init(wrapper, sizeof(vertices) / sizeof(float), sizeof(indices) / sizeof(unsigned int));
	VAO.setVertexAttribPointersf(0, 3, 5, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));
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
		glClearColor(0.0f, 0.0f, 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		// ========================= ImGui ==============================
		ImGui::Begin("Window");
		ImGui::Text("Selection Screen OmegaLol");
		ImGui::Checkbox("Draw Triangle", &drawTriangle);
		ImGui::SliderFloat("Move Left & Right", &leftRightMove, -2.0f, 2.0f);
		ImGui::SliderFloat("Scale Image", &scaleRate, 0.0f, 3.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		// <---------------- Rendering Code --------------------> \\

		
		if (drawTriangle) {
			texture.bind();
			renderer.draw(VAO, shader);
		}
		
		// Switch buffers lol
		glfwSwapBuffers(window.getWindow());

		// ---------------- Changing Code -------------------- \\

		view = glm::translate(model, glm::vec3(leftRightMove, 0.0f, 0.0f));	
		view = glm::scale(model, glm::vec3(scaleRate, scaleRate, scaleRate));

		glm::mat4 MVP = model * proj * view;
		shader.setUniformMat4f("u_MVP", MVP);
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
	float vertices2[] =
	{
		0.6f, 0.6f, -5.0f, // Bottom Left
		0.6f, 0.8f,  0.0f, // Top Left
		0.9f, 0.6f,  0.0f

	};
	unsigned int indices2[] =
	{
		0, 1, 2
	};

	texture.init();
	texture.setVertAttribs(1, 2, 5, 3);

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