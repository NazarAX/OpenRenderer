//
// Created by Nazarii on 11/28/2024.
//

#include "Application.h"
#include "System/Input.h"
#include <iostream>
#include <Rendering/Serializer.h>

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

    EditorUI::Init();

    //Configuring editorUI

    hierarchyPanel = std::make_shared<HierarchyPanel>();
    sceneViewPanel = std::make_shared<SceneViewPanel>();
    settingsPanel = std::make_shared<SettingsPanel>();




    Material snailMat = Material{Texture("res/textures/snail_color.png"), Shader("res/shaders/modelShader.glsl"), "snailMaterial"};
    Material trophyMat = Material{Texture("res/textures/DefaultMaterial_baseColor.jpeg"), Shader("res/shaders/modelShader.glsl"), "trophyMaterial"};

    auto snail1 = scene.CreateEntity("snail 1");
    auto snail2 = scene.CreateEntity("snail 2");
    auto trophy = scene.CreateEntity("trophy");

    scene.AddComponent<Transform>(trophy);

    scene.GetComponent<Transform>(trophy).position = glm::vec3(10.0f, 20.0f, 3.0f);
    scene.GetComponent<Transform>(trophy).rotation = glm::vec3(40.0f, 10.0f, 2.0f);

    scene.AddComponent<Model>(snail1,  "res/models/Snail.obj");
    scene.AddComponent<Transform>(snail1);
    scene.AddComponent<Material>(snail1, snailMat);

    scene.GetComponent<Transform>(snail1).position = glm::vec3(10.0f, 0.0f, 3.0f);
    scene.GetComponent<Transform>(snail1).rotation = glm::vec3(40.0f, 10.0f, 2.0f);


    scene.AddComponent<Model>(snail2,  "res/models/scene.gltf");
    scene.AddComponent<Transform>(snail2);
    scene.AddComponent<Material>(snail2, trophyMat);



    scene.GetComponent<Transform>(snail1).position = glm::vec3(0.0f, 0.0f, 3.0f);
    scene.GetComponent<Transform>(snail1).rotation = glm::vec3(40.0f, 10.0f, 2.0f);

    Serializer::Serialize(&scene, "scene.yaml");
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

        EditorUI::Begin();

        hierarchyPanel->Draw();
        settingsPanel->Draw(frameStats);
        sceneViewPanel->Draw(frameBuffer.get(), camera.get());

        EditorUI::End();

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