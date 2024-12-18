//
// Created by Nazarii on 11/28/2024.
//

#include "Application.h"
#include "System/Input.h"
#include <iostream>
#include <Rendering/Serializer.h>
#include "UI/UI.h"
#include "UI/Panel.h"

Application* Application::instance;

Application::Application()
    :
    window({1920, 1080, "OpenRenderer"}),
    frameStats({0, 0}), selected(entt::null)
{

    window.SetEventCallback(Application::EventCallback);
    Window::currentWindow = &window;

    //DefaultScene
    scene = Serializer::Deserialize("/Users/nazarii/Desktop/XScene.yaml");
    selected = scene->GetEntity("Gorilla");

    frameBuffer = std::make_shared<FrameBuffer>(window.GetWidth(), window.GetHeight());

    cameraEntity = scene->GetPrimaryCamera();
    Camera& camera = scene->AddComponent<Camera>(cameraEntity, true);
    Transform& transform = scene->AddComponent<Transform>(cameraEntity);
    camera.UpdateView(transform);

    cameraController = std::make_shared<CameraController>(camera, transform, 0.2);

    renderer = std::make_unique<Renderer>();
    renderer->AddLight(PointLight{glm::vec3(0), glm::vec3(1), 1});

    UI::Init();

}


Application::~Application()
{

}

void Application::Run()
{

    while (true)
    {
        frameStats.Begin();
        Camera& camera = scene->GetComponent<Camera>(cameraEntity);

        frameBuffer->Bind();
        renderer->BeginScene(camera);
        renderer->DrawScene(*scene.get());
        frameBuffer->Unbind();

        //Drawing UI
        UI::Begin();
        UI::DrawMainMenuBar();

        UI::DrawHierarchyPanel(scene.get(), selected);
        UI::DrawSceneViewPanel(frameBuffer.get(), camera, selected, scene.get());
        UI::DrawSettingsPanel(frameStats);

        UI::End();

        Input::update();
        cameraController->Update();
        // Update window
        window.Update();

        frameStats.End();
    }
}






void Application::EventCallback(Events::Event& e)
{

    if (e.GetType() == Events::Event::EventType::WindowResizeEvent)
    {
        Events::WindowResizeEvent& resizeEvent = (Events::WindowResizeEvent&)e;
    }

    if (e.GetType() == Events::Event::EventType::WindowCloseEvent)
    {
        std::exit(0);
    }
}