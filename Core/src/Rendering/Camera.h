//
// Created by Nazarii on 11/25/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <glm/glm.hpp>

#include "Interface/FrameBuffer.h"

struct CameraTransform
{
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;

    float zoom;
    float pitch;
    float yaw;
};


class Camera
{
private:
    CameraTransform transform;
    glm::mat4 projection;
    glm::mat4 view;
    FrameBuffer* frameBuffer;
private:
    void UpdateView();
public:
    Camera() {}
    Camera(float w, float h, float fov);

    void Reset(float width, float height, float fov = 90.0f);
    void Move(glm::vec3 delta);
    void SetPosition(glm::vec3 _pos);

    void SetZoom(float zoom);
    void SetPitch(float pitch);
    void SetYaw(float yaw);
    void Turn(float delta_pitch, float delta_yaw);

    glm::vec3 GetRight() const { return glm::cross(transform.front, transform.up); }
    glm::vec3 GetFront() const { return transform.front; }
    glm::vec3 GetPosition() const{ return transform.pos; }

    glm::mat4 GetView() const { return view; }
    glm::mat4 GetProjection() const { return projection; }
    static glm::mat4 GetModel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale=glm::vec3(1));

    void SetFrameBuffer(FrameBuffer* _fb) { frameBuffer = _fb; }
};


class CameraController
{
private:
    std::shared_ptr<Camera> camera;
public:
    CameraController(std::shared_ptr<Camera> _camera) : camera(_camera){}
    ~CameraController() {}

    void UpdateInputs();
};




#endif //CAMERA_H
