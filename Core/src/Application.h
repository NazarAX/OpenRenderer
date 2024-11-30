//
// Created by Nazarii on 11/28/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "System/Window.h"
#include "System/Events/Event.h"
#include "UI/UserInterface.h"
#include "Rendering/Camera.h"
#include "Rendering/Renderer.h"
#include "Rendering/Scene.h"
#include <memory>

#include "Interface/FrameBuffer.h"


class Application
{
private:
    static Application* instance;
    Window window;
    UserInterface ui;
    Model model; // sample model
    Scene scene;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<FrameBuffer> frameBuffer;

private:
    Application();
    void SetupGL();
public:
    ~Application();

    void Run();
    Scene* GetScene() { return &scene; }

    static void EventCallback(Events::Event& event);

    static Application* GetInstance()
    {
        if (instance == nullptr)
          instance = new Application();
        return instance;
    }


};



#endif //APPLICATION_H
