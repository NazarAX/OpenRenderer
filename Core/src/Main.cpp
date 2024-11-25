#include "App/Window.h"
#include "Rendering/Abstractions.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <memory>
#include "App/Input.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "Rendering/FrameBuffer.h"
#include "Rendering/Buffers.h"
#include "Exception.h"
#include "Assets.h"
#include "Model.h"


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

static void updateCamera(std::shared_ptr<Camera> camera) {


    // Handle input
    if (Input::isKeyDown(KeyCode::W)) camera->move(camera->getFront() * 0.1f);
    if (Input::isKeyDown(KeyCode::S)) camera->move(-camera->getFront() * 0.1f );
    if (Input::isKeyDown(KeyCode::D)) camera->move(camera->getRight() * 0.1f);
    if (Input::isKeyDown(KeyCode::A)) camera->move(-camera->getRight() * 0.1f);


    if (Input::isMouseButtonPressed(MouseCode::Button1) )
    {
        camera->turn(Input::getMouseDelta().x * 2, Input::getMouseDelta().y * 2);
    }
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
    //
    glEnable(GL_DEPTH_TEST);

    camera = std::make_shared<Camera>(600, 600, 45);
    camera->setPosition(glm::vec3(0.0f, 0.5f, -3.0f));


    Shader shader("res/shaders/modelShader.glsl");


    Model model;
    model.LoadFromFile("res/models/snail.obj");

    Texture texture("res/textures/snail_color.png");
    texture.bind();


    Renderer renderer;


    shader.Bind();

    
    while (window.Active) 
    {    
        Input::update(); // Update input system, including mouse positions

        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


        updateCamera(camera);

        //renderer.beginScene(camera);
        //renderer.drawQuad(defaultShader, { {0, 0, 0} });

        shader.Bind();
        shader.setUniformMatrix4fv("uModel", glm::mat4(1.0f));
        shader.setUniformMatrix4fv("uView", camera->getView());
        shader.setUniformMatrix4fv("uProjection", camera->getProjection());
        shader.setUniformMatrix4fv("uTexture", texture.getId());

        renderer.beginScene(camera);
        renderer.drawModel(model);


        // Update window
        window.Update();
	}
}
