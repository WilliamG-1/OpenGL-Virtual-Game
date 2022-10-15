#include "Window.h"
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title)
	:
	window(nullptr), screenWidth(width), screenHeight(height)
{
	

	window = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Error, window creation failed!" << std::endl;
		glfwTerminate();
	}	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	init();
}

void Window::init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
	}
	glViewport(0, 0, screenWidth, screenHeight);
}


GLFWwindow* Window::getWindow() const
{
	return window;
}

Window::~Window()
{
	glfwDestroyWindow(window);
	window = nullptr;
}