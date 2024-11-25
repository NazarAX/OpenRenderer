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





	void update() {

		if (Window::currentWindow == nullptr)
		{
			std::cerr << "Error: currentWindow is nullptr!" << std::endl;
		}

		// Update logic
		double xpos, ypos;
		glfwGetCursorPos(Window::currentWindow->GetHandle(), &xpos, &ypos);
		glm::vec2 currentMousePos = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));

		deltaMousePos = currentMousePos - mousePos;
		deltaMousePos.y = -deltaMousePos.y;
		mousePos = currentMousePos;

	}

	glm::vec2 getMouseDelta() {
		return deltaMousePos;
	}

	glm::vec2 getMousePos() {

		return mousePos;
	}



}
