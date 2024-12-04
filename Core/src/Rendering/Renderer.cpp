#include "Renderer.h"
#include <glad/glad.h>
#include "Interface/Exception.h"
#include "GLFW/glfw3.h"
#include <iostream>






Renderer::Renderer()
	: sceneLight()
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
	glEnable(GL_DEPTH_TEST);
}


void Renderer::DrawQuad(Shader& shader)
{

	quadVA.Bind();
	shader.Bind();
	quadIB.Bind();


	GL(glDrawElements(GL_TRIANGLES, quadIB.GetCount(), GL_UNSIGNED_INT, 0));
}


void Renderer::DrawModel(const Model& model, Material& material, const Transform& transform)
{
	std::vector<Mesh> meshes = model.GetMeshes();

	for (Mesh mesh : meshes)
	{
		mesh.vertexArray.Bind();
		mesh.indexBuffer.Bind();

		SetupShaderUniforms(material, transform);

		glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	}
}

void Renderer::SetupShaderUniforms(Material &material, Transform transform)
{

	static glm::vec3 lightDisplacement = glm::vec3(0.0f, 0.0f, 0.0f);
	

	material.Shader.Bind();
	material.Albedo.Bind();

	glm::mat4 modelMatrix = Camera::GetModel(transform.position, transform.rotation);

	material.Shader.SetUniformMatrix4fv("uModel", modelMatrix);
	material.Shader.SetUniformMatrix4fv("uView", camera->GetView());
	material.Shader.SetUniformMatrix4fv("uProjection", camera->GetProjection());
	material.Shader.SetUniformMatrix4fv("uTexture", material.Albedo.GetId());

	PointLight light = sceneLight.PointLights[0];
	material.Shader.SetUniform3f("uLightColor", light.Color);
	material.Shader.SetUniform3f("uLightPos", light.Position + lightDisplacement);
	material.Shader.SetUniform1f("uLightIntensity", light.Intensity);
	material.Shader.SetUniform3f("uAmbientLight", glm::vec3(0.5f, 0.5f, 0.5f));


}

void Renderer::DrawScene(Scene &scene)
{
	for (entt::entity entity : scene.GetEntitiesWithComponent<Model>())
	{
		Model& model = scene.GetComponent<Model>(entity);
		Transform& transform = scene.GetComponent<Transform>(entity);
		Material& material = scene.GetComponent<Material>(entity);

		DrawModel(model, material, transform);
	}
}


void Renderer::BeginScene(std::shared_ptr<Camera> camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.529f,0.808f,0.922f, 1.0);

	this->camera = camera;
}

void Renderer::EndScene()
{
	
}