//
// Created by Nazarii on 11/25/2024.
//

#include "Camera.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <ostream>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "Interface/Exception.h"
#include "Model.h"
#include "System/Input.h"


Camera::Camera(float w, float h, float fov, bool primary) : primary(primary), up(0, 1, 0)
{

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 1000.0f; // Far clipping plane

	float aspectRatio = (float)w / (float)h;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

}

void Camera::UpdateView(Transform& transform)
{
	this->transform = transform;
	front.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	front.y = sin(glm::radians(transform.rotation.x));
	front.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
	front = glm::normalize(front);

	// Calculate the right vector
	glm::vec3 right = glm::normalize(glm::cross(front, up));

	// Rotate the up vector around the front axis for roll
	float rollAngle = glm::radians(transform.rotation.z); // Roll in radians
	glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), rollAngle, front); // Rotate around front
	up = glm::mat3(rollMatrix) * glm::vec3(0, 1, 0);

	glm::vec3 target = transform.position + front;
	this->view = glm::lookAt(transform.position, target, up);

}


void Camera::Reset(float width, float height, float fov) {

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 1000.0f; // Far clipping plane

	float aspectRatio = (float)width / (float)height;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

}



void Camera::SetZoom(float zoom)
{

}







void CameraController::Update()
{
	// Handle input
	if (Input::isKeyDown(Input::KeyCode::W))
	{
		transform.position += camera.GetFront() * sensitivity;
		camera.UpdateView(transform);
	}
	if (Input::isKeyDown(Input::KeyCode::S))
	{
		transform.position -= camera.GetFront() * sensitivity;
		camera.UpdateView(transform);
	}
	if (Input::isKeyDown(Input::KeyCode::D))
	{
		transform.position += camera.GetRight() * sensitivity;
		camera.UpdateView(transform);
	}
	if (Input::isKeyDown(Input::KeyCode::A))
	{
		transform.position -= camera.GetRight() * sensitivity;
		camera.UpdateView(transform);
	}

	if (Input::isMouseButtonPressed(Input::MouseCode::Button1) )
	{
		transform.rotation.y += Input::getMouseDelta().x * 0.2f;
		transform.rotation.x += Input::getMouseDelta().y * 0.2f;
		camera.UpdateView(transform);
	}
}