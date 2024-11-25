#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <ostream>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "Exception.h"





Camera::Camera(float w, float h, float fov) :
	pos(0, 0, 0), pitch(0), yaw(90), up(0, 1, 0), zoom(2)
{
	reset(w, h, fov=90);
}

void Camera::updateView()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	glm::vec3 target = pos + glm::normalize(front); // Assuming the camera looks down the negative Z-axis

	this->view = glm::lookAt(pos, target, up);
}


void Camera::reset(float width, float height, float fov) {

	float nearPlane = 0.1f; // Near clipping plane
	float farPlane = 100.0f; // Far clipping plane

	float aspectRatio = (float)width / (float)height;
	this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane) * zoom;
}

void Camera::setPosition(glm::vec3 _pos)
{
	this->pos = _pos;
	updateView();
}

void Camera::setZoom(float zoom)
{
	this->zoom = zoom;
}

void Camera::setYaw(float _yaw)
{
	this->yaw = _yaw;
	updateView();
}

void Camera::turn(float delta_pitch, float delta_yaw)
{
	this->pitch += glm::radians(delta_yaw);
	this->yaw += glm::radians(delta_pitch);
	updateView();
}

void Camera::setPitch(float _pitch)
{
	this->pitch = _pitch;
	updateView();
}

glm::mat4 Camera::getModel(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	glm::mat4 model = glm::mat4(1.0f); // Identity matrix

	// Scale the model
	model = glm::scale(model, scale);

	// Rotate the model
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotate around Z
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotate around Y
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotate around X

	// Translate the model
	model = glm::translate(model, position);

	return model;
}

void Camera::move(glm::vec3 _pos)
{
	this->pos += _pos;
	updateView();
}






Renderer::Renderer()
{

	float quadVertices[] = {
		// Position
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
	};

	float quadUV[] ={
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	unsigned int quadIndices[] = {
		0, 1, 2, // First triangle
		0, 2, 3  // Second triangle
	};

	quadIB = IndexBuffer(quadIndices, 6);
	VertexBuffer uvBuffer =VertexBuffer(quadUV, sizeof(quadUV));
	VertexBuffer vertBuffer = VertexBuffer(quadVertices, sizeof(quadVertices));

	quadVA.AddBuffer(vertBuffer, Coordinates, 2);
	quadVA.AddBuffer(uvBuffer, TexCoords, 2);


	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f); // Adjust the values as needed

}



void Renderer::draw(VertexArray& va, Shader& shader, IndexBuffer& ib)
{
	va.Bind();
	shader.Bind();
	ib.Bind();


	GL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::draw(VertexArray& va, Shader& shader, IndexBuffer& ib, Transform transform)
{
	va.Bind();
	shader.Bind();

	glm::mat4 modelMatrix = Camera::getModel(transform.position, transform.rotation);
	shader.setUniformMatrix4fv("model", modelMatrix);
	shader.setUniformMatrix4fv("view", camera->getView());
	shader.setUniformMatrix4fv("projection", camera->getProjection());

	GL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::drawQuad(Shader& shader)
{
	
	quadVA.Bind();
	shader.Bind();
	quadIB.Bind();


	GL(glDrawElements(GL_TRIANGLES, quadIB.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::drawQuad(Shader& shader, Transform transform)
{
	shader.Bind();
	glm::mat4 modelMatrix = Camera::getModel(transform.position, transform.rotation);
	shader.setUniformMatrix4fv("model", modelMatrix);
	shader.setUniformMatrix4fv("view", camera->getView());
	shader.setUniformMatrix4fv("projection", camera->getProjection());

	draw(quadVA, shader, quadIB);
}

void Renderer::drawModel(const Model& model)
{
	std::vector<Mesh> meshes = model.GetMeshes();

	for (Mesh mesh : meshes)
	{
		mesh.vertexArray.Bind();
		mesh.indexBuffer.Bind();

		glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::beginScene(std::shared_ptr<Camera> camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);

	this->camera = camera;
}

void Renderer::endScene() 
{
	
}