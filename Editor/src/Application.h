//
// Created by Nazarii on 11/28/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "System/Window.h"
#include "System/Events/Event.h"
#include "Rendering/Camera.h"
#include "Rendering/Renderer.h"
#include "Rendering/Scene.h"

#include "Interface/FrameBuffer.h"
#include "Rendering/Serializer.h"



class Application {
private:
    static Application* instance;
    Window window;
    std::shared_ptr<Scene> scene;
    FrameStats frameStats;
    std::unique_ptr<Renderer> renderer;
    std::shared_ptr<CameraController> cameraController;
    std::shared_ptr<FrameBuffer> frameBuffer;
    entt::entity selected;
    entt::entity cameraEntity;
    Serializer serializer;

private:
    Application();
public:
    ~Application();

    void Run();

    Scene* GetScene() { return scene.get(); }
    void SetScene(std::shared_ptr<Scene> scene) { this->scene = scene; }

    static void EventCallback(Events::Event& event);

    static Application* GetInstance()
    {
        if (instance == nullptr)
          instance = new Application();
        return instance;
    }


};



#endif //APPLICATION_H
