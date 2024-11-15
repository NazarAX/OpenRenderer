#include "Input.h"
#include "Window.h" // Assuming the Window class wraps around GLFW
#include <GLFW/glfw3.h>  // GLFW header for key and mouse input functions
#include <iostream>

namespace Input
{
	// Check if a specific key is down (pressed)
	bool isKeyDown(KeyCode key)
	{
		if (Window::currentWindow == nullptr)
		{
			std::cerr << "Error: currentWindow is nullptr!" << std::endl;
			return false;
		}

		// GLFW uses a key state enum with GLFW_PRESS and GLFW_RELEASE
		int state = glfwGetKey(Window::currentWindow->GetHandle(), static_cast<int>(key));
		return (state == GLFW_PRESS);
	}

	// Check if a specific mouse button is pressed
	bool isMouseButtonPressed(MouseCode button)
	{
		if (Window::currentWindow == nullptr)
		{
			std::cerr << "Error: currentWindow is nullptr!" << std::endl;
			return false;
		}

		// GLFW uses a button state enum with GLFW_PRESS and GLFW_RELEASE
		int state = glfwGetMouseButton(Window::currentWindow->GetHandle(), static_cast<int>(button));
		return (state == GLFW_PRESS);
	}

	// Get the X position of the mouse
	float getMouseX()
	{
		if (Window::currentWindow == nullptr)
		{
			std::cerr << "Error: currentWindow is nullptr!" << std::endl;
			return 0.0f;
		}

		double xpos, ypos;
		glfwGetCursorPos(Window::currentWindow->GetHandle(), &xpos, &ypos);
		return static_cast<float>(xpos);
	}

	// Get the Y position of the mouse
	float getMouseY()
	{
		if (Window::currentWindow == nullptr)
		{
			std::cerr << "Error: currentWindow is nullptr!" << std::endl;
			return 0.0f;
		}

		double xpos, ypos;
		glfwGetCursorPos(Window::currentWindow->GetHandle(), &xpos, &ypos);
		return static_cast<float>(ypos);
	}

	// Get the mouse position as a glm::vec2
	glm::vec2 getMousePos()
	{
		if (Window::currentWindow == nullptr)
		{
			std::cerr << "Error: currentWindow is nullptr!" << std::endl;
			return glm::vec2(0.0f, 0.0f);
		}

		double xpos, ypos;
		glfwGetCursorPos(Window::currentWindow->GetHandle(), &xpos, &ypos);
		return glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
	}
}
