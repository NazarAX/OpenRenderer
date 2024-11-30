//
// Created by Nazarii on 11/28/2024.
//

#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "System/Input.h"
#include <iostream>



Application* Application::instance;

Application::Application()
    :
    window({1920, 1080, "OpenRenderer"}),
    ui(window),
    scene("BaseScene")
{

    window.SetEventCallback(Application::EventCallback);
    Window::currentWindow = &window;

    SetupGL();

    glEnable(GL_DEPTH_TEST);


    ui.AddPanel<HierarchyPanel>();

    camera = std::make_shared<Camera>(600, 600, 45);
    camera->setPosition(glm::vec3(0.0f, 0.5f, -3.0f));


    cameraController = std::make_shared<CameraController>(camera);

    renderer = std::make_shared<Renderer>();
    renderer->AddLight(PointLight{glm::vec3(0), glm::vec3(1), 1});


    snail1 = scene.CreateEntity("snail 1");
    auto snail2 = scene.CreateEntity("snail 2");

    scene.AddComponent<Model>(snail1, "res/models/snail.obj");
    scene.AddComponent<Transform>(snail1);

    scene.GetComponent<Transform>(snail1).position = glm::vec3(10.0f, 0.0f, 3.0f);
    scene.GetComponent<Transform>(snail1).rotation = glm::vec3(40.0f, 10.0f, 2.0f);


    scene.AddComponent<Model>(snail2, "res/models/snail.obj");
    scene.AddComponent<Transform>(snail2);


    scene.GetComponent<Transform>(snail1).position = glm::vec3(0.0f, 0.0f, 3.0f);
    scene.GetComponent<Transform>(snail1).rotation = glm::vec3(40.0f, 10.0f, 2.0f);
}


Application::~Application()
{

}

void Application::Update()
{
    Input::update(); // Update input system, including mouse positions

    renderer->BeginScene(camera);

    renderer->DrawScene(scene);

    ui.Draw();

    cameraController->UpdateInputs();
    // Update window
    window.Update();
}





void Application::SetupGL()
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


void Application::EventCallback(Events::Event& e)
{

    if (e.GetType() == Events::Event::EventType::WindowResizeEvent)
    {
        Events::WindowResizeEvent& resizeEvent = (Events::WindowResizeEvent&)e;
        GetInstance()->camera->reset(resizeEvent.GetWidth(), resizeEvent.GetHeight());
    }

    if (e.GetType() == Events::Event::EventType::WindowCloseEvent)
    {
        std::exit(0);
    }
}