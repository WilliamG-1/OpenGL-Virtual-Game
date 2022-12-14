#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();
	void init();

	GLFWwindow* getWindow() const;

private:
	GLFWwindow* window;

	// Variables
	int screenWidth;
	int screenHeight;
};

