//
// Created by Nazarii on 11/25/2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <glm/glm.hpp>

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
private:
    void updateView();
public:
    Camera() {}
    Camera(float w, float h, float fov);

    void reset(float width, float height, float fov = 45.0f);
    void move(glm::vec3 delta);
    void setPosition(glm::vec3 _pos);

    void setZoom(float zoom);
    void setPitch(float pitch);
    void setYaw(float yaw);
    void turn(float delta_pitch, float delta_yaw);

    glm::vec3 getRight() const { return glm::cross(transform.front, transform.up); }
    glm::vec3 getFront() const { return transform.front; }
    glm::vec3 getPosition() const{ return transform.pos; }

    glm::mat4 getView() const { return view; }
    glm::mat4 getProjection() const { return projection; }
    static glm::mat4 getModel(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
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
