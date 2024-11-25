#pragma once
#include "Rendering/Abstractions.h"
#include "Rendering/Buffers.h"
#include <memory>

#include "Model.h"

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
};



class Camera
{
private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	float zoom;
	float pitch;
	float yaw;

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

	glm::vec3 getRight() const { return glm::cross(front, up); }
	glm::vec3 getFront() const { return this->front; }
	glm::vec3 getPosition() const{ return this->pos; }
	glm::mat4 getView() const { return view; }
	glm::mat4 getProjection() const { return projection; }
	static glm::mat4 getModel(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
};






class Renderer
{
public:
	Renderer();
	~Renderer() {}

	void beginScene(std::shared_ptr<Camera> camera);
	void draw(VertexArray& va, Shader& shader, IndexBuffer& ib);
	void draw(VertexArray& va, Shader& shader, IndexBuffer& ib, Transform position);
	void drawQuad(Shader& shader);
	void drawQuad(Shader& shader, Transform transform);
	void drawModel(const Model& model);
	void endScene();
public:
	VertexArray quadVA;
	IndexBuffer quadIB;
	std::shared_ptr<Camera> camera;
};

