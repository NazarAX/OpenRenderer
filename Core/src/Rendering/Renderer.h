#pragma once
#include "Interface/Abstractions.h"
#include "Interface/Buffers.h"
#include "Scene.h"
#include "Camera.h"
#include <memory>

#include "Model.h"


struct PointLight
{
	glm::vec3 Position;
	glm::vec3 Color;
	float Intensity;
};

struct SceneLightInfo
{
	std::vector<PointLight> PointLights;
};


class Renderer
{
public:
	Renderer();
	~Renderer() {}

	void SetupShaderUniforms(Material material, Transform transform);

	void BeginScene(std::shared_ptr<Camera> camera);
	void DrawQuad(Shader& shader);
	void DrawModel(const Model& model, Material material, const Transform& tranform);
	void DrawScene(Scene& scene);
	void EndScene();

	void AddLight(PointLight light) {
		sceneLight.PointLights.push_back(light);
	}

public:
	SceneLightInfo sceneLight;//example

	VertexArray quadVA;
	IndexBuffer quadIB;
	std::shared_ptr<Camera> camera;
};

