//
// Created by Nazarii on 11/28/2024.
//

#include "Application.h"
#include "System/Input.h"
#include <iostream>


Application* Application::instance;

Application::Application()
    :
    window({1920, 1080, "OpenRenderer"}),
    scene("BaseScene"), frameStats({0, 0})
{

    window.SetEventCallback(Application::EventCallback);
    Window::currentWindow = &window;

    

    frameBuffer = std::make_shared<FrameBuffer>(window.GetWidth(), window.GetHeight());

    camera = std::make_shared<Camera>(600, 600, 45);
    camera->SetPosition(glm::vec3(0.0f, 0.5f, -3.0f));



    cameraController = std::make_shared<CameraController>(camera);

    renderer = std::make_unique<Renderer>();
    renderer->AddLight(PointLight{glm::vec3(0), glm::vec3(1), 1});

    editorInfo = new EditorInfo();

    editorUI = EditorUI::GetInstance();

    //Configuring editorUI
    {
        std::shared_ptr<HierarchyPanel> hierarchy_panel = std::make_shared<HierarchyPanel>();
        std::shared_ptr<SceneViewPanel> scene_view_panel = std::make_shared<SceneViewPanel>();
        std::shared_ptr<RenderStatsPanel> render_stats_panel = std::make_shared<RenderStatsPanel>();
        std::shared_ptr<PropertiesPanel> properties_panel = std::make_shared<PropertiesPanel>();

        scene_view_panel->SetViewCamera(this->camera.get());
        scene_view_panel->SetFrameBuffer(this->frameBuffer.get());
        render_stats_panel->SetFrameStats(&frameStats);


        editorUI->AddPanel(hierarchy_panel);
        editorUI->AddPanel(scene_view_panel);
        editorUI->AddPanel(render_stats_panel);
        editorUI->AddPanel(properties_panel);
    }



    auto snail1 = scene.CreateEntity("snail 1");
    auto snail2 = scene.CreateEntity("snail 2");
    auto trophy = scene.CreateEntity("trophy");
    scene.AddComponent<Model>(trophy, "res/models/scene.gltf");
    scene.AddComponent<Transform>(trophy);

    scene.GetComponent<Transform>(trophy).position = glm::vec3(10.0f, 20.0f, 3.0f);
    scene.GetComponent<Transform>(trophy).rotation = glm::vec3(40.0f, 10.0f, 2.0f);

    scene.AddComponent<Model>(snail1,  "res/models/scene.gltf");
    scene.AddComponent<Transform>(snail1);

    scene.GetComponent<Transform>(snail1).position = glm::vec3(10.0f, 0.0f, 3.0f);
    scene.GetComponent<Transform>(snail1).rotation = glm::vec3(40.0f, 10.0f, 2.0f);


    scene.AddComponent<Model>(snail2,  "res/models/scene.gltf");
    scene.AddComponent<Transform>(snail2);


    scene.GetComponent<Transform>(snail1).position = glm::vec3(0.0f, 0.0f, 3.0f);
    scene.GetComponent<Transform>(snail1).rotation = glm::vec3(40.0f, 10.0f, 2.0f);
}


Application::~Application()
{

}

void Application::Run()
{

    while (true)
    {

        frameStats.Begin();

        frameBuffer->Bind();
        renderer->BeginScene(camera);
        renderer->DrawScene(scene);
        frameBuffer->Unbind();

        editorUI->Draw();

        Input::update();
        cameraController->UpdateInputs();
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