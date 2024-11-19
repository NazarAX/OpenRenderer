#include "App/Window.h"
#include "Rendering/Abstractions.h"
#include "Renderer.h"
#include "GL/glew.h"
#include "model.embed"
#include <memory>
#include "App/Input.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Rendering/FrameBuffer.h"
#include "Rendering/Buffers.h"
#include "Exception.h"
#include "Assets.h"


static void setupGL()
{

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Could not initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST); // Optional: synchronous messages (blocks until message is processed)
	glEnable(GL_DEBUG_OUTPUT);

	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
		{
			// Print the debug message
			std::cout << "OpenGL Debug Message: " << message << std::endl;

			// Optionally, you can also print additional details about the message
			std::cout << "Source: " << source << std::endl;
			std::cout << "Type: " << type << std::endl;
			std::cout << "ID: " << id << std::endl;
			std::cout << "Severity: " << severity << std::endl;

			// You can add more custom handling based on the message source, type, or severity
			if (severity == GL_DEBUG_SEVERITY_HIGH) {
				std::cerr << "Critical OpenGL Error!" << std::endl;
			}
		}, nullptr);
}

int main() 
{
    Window window({ 600, 600, "Name" });
    Window::currentWindow = &window;

    setupGL();

    std::shared_ptr<Camera> camera = std::make_shared<Camera>(600, 600, 45);
    camera->setPosition(glm::vec3(0.0f, 0.5f, -3.0f));

    Shader shader("C:/Users/Nazarii/OneDrive/Desktop/OpenRenderer/build/res/shaders/defaultShader.glsl");

    float quadVertices[] = {
        // Position       // TexCoords
        -1.0f,  1.0f,    0.0f, 0.0f, // Top-left (Y flipped)
        -1.0f, -1.0f,    0.0f, 1.0f, // Bottom-left
         1.0f, -1.0f,    1.0f, 1.0f, // Bottom-right
         1.0f,  1.0f,    1.0f, 0.0f  // Top-right (Y flipped)
    };

    unsigned int quadIndices[] = {
        0, 1, 2, // First triangle
        0, 2, 3  // Second triangle
    };
    
    VertexArray array(quadVertices, sizeof(quadVertices), VertexLayout{2, 0, 2});
    IndexBuffer ibo(quadIndices, 6);


    while (window.Active) 
    {    
        // Handle input
        if (Input::isKeyDown(KeyCode::W)) camera->move(glm::vec3(0, 0, 0.1f));
        if (Input::isKeyDown(KeyCode::S)) camera->move(glm::vec3(0, 0, -0.1f));
        if (Input::isKeyDown(KeyCode::A)) camera->move(glm::vec3(0.1f, 0, 0.0f));
        if (Input::isKeyDown(KeyCode::D)) camera->move(glm::vec3(-0.1f, 0, 0));

        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        
        array.Bind();
        ibo.Bind();
        shader.bind();

        //// Update camera uniform

        //// Draw the quad
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Update window
        window.Update();
	}
}
