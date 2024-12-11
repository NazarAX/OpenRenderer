#include "Window.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "Input.h"
#include "Interface/Abstractions.h"

using namespace Events;

bool Window::s_GlfwInitialized;
Window* Window::currentWindow;


void FrameStats::Begin()
{
	Timer = glfwGetTime();
}

void FrameStats::End()
{
	DeltaTime = glfwGetTime() - Timer;
}

Window::Window(WindowProps props) 
	: Active(true)
{
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;
	m_Data.Title = props.Title;
	m_Data.WindowPtr = this;

	SetEventCallback(DefaultEventCallback);

	if (!s_GlfwInitialized)
	{
		int status = glfwInit();
		s_GlfwInitialized = status;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
	#endif

	m_Handle = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
	glfwShowWindow(m_Handle);
	glfwMakeContextCurrent(m_Handle);
	glfwSetWindowUserPointer(m_Handle, &m_Data);

	SetupGL();

	

	glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			data->Width = width;
			data->Height = height;

			WindowResizeEvent e(width, height);
			glViewport(0, 0, width, height);

			data->EventCallback(e);
		});

	glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			data->WindowPtr->Active = false;
			data->EventCallback(e);
		});

	glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			KeyEvent e(key, action);
			data->EventCallback(e);
		});


	glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			MouseButtonEvent e(button, action);
			data->EventCallback(e);
		});

	glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent e(xOffset, yOffset);
			data->EventCallback(e);
		});

	glfwSetCursorPosCallback(m_Handle, MouseMovedCallback);
}



void Window::MouseMovedCallback(GLFWwindow* window, double xPos, double yPos)
{

	WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

	MouseMovedEvent e(xPos, yPos);
	data->EventCallback(e);

	MouseMovedEvent::s_PrevX = xPos;
	MouseMovedEvent::s_PrevY = yPos;

}


void Window::DefaultEventCallback(Event& e)
{

}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Handle);
	m_Handle = nullptr;
}


void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Handle);
}



void Window::SetupGL()
{

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

	InitDefaultStructures();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;


#ifdef DEBUG_GL
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Optional: ensures messages are processed immediately
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
            std::cerr << "OpenGL Debug Message: " << message << "\n"
                    << "Source: " << source << ", Type: " << type
                    << ", ID: " << id << ", Severity: " << severity << std::endl;

            if (severity == GL_DEBUG_SEVERITY_HIGH) {
                std::cerr << "Critical OpenGL Error!" << std::endl;
            }
        },
        nullptr);
#endif
}