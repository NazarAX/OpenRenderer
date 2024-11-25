#include "System/Window.h"
#include "Interface/Abstractions.h"
#include "Rendering/Renderer.h"
#include <glad/glad.h>
#include <memory>
#include "System/Input.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Interface/FrameBuffer.h"
#include "Interface/Buffers.h"
#include "Interface/Exception.h"
#include "Assets.h"
#include "Rendering/Model.h"


static void setupGL()
{
    
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }

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

std::shared_ptr<Camera> camera;

static void handleEvent(Events::Event& e)
{
    if (e.GetType() == Events::Event::EventType::WindowResizeEvent)
    {
        Events::WindowResizeEvent& resizeEvent = (Events::WindowResizeEvent&)e;
        camera->reset(resizeEvent.GetWidth(), resizeEvent.GetHeight());
    }
}

int main()
{

    Window window({ 1920, 1080, "Name" });
    window.SetEventCallback(handleEvent);
    Window::currentWindow = &window;

    setupGL();

    glEnable(GL_DEPTH_TEST);

    camera = std::make_shared<Camera>(600, 600, 45);
    camera->setPosition(glm::vec3(0.0f, 0.5f, -3.0f));

    CameraController cameraController(camera);

    Model model;
    model.LoadFromFile("res/models/snail.obj");


    Renderer renderer;



    while (window.Active)
    {
        Input::update(); // Update input system, including mouse positions

        renderer.BeginScene(camera);
        renderer.DrawModel(model);


        cameraController.UpdateInputs();
        // Update window
        window.Update();
	}
}