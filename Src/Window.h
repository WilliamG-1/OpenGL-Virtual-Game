#pragma once
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw.h>
#include <Imgui/imgui_impl_opengl3.h>
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
	void resizeWindow();

	// Variables
	int screenWidth;
	int screenHeight;
};

