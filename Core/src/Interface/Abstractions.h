#pragma once
#include <memory.h>
#include <string>
#include <glm/glm.hpp>
#include <vector>



enum ShaderType
{
	Vertex,
	Fragment
};

/*
	Shader abstraction
*/

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& filename);
	Shader(const std::string& vertex, const std::string& fragment, const std::string& name = "");
	~Shader() = default;

	static std::string ParseShader(const std::string& src, ShaderType type);
	static unsigned int CompileShader(std::string src, const std::string& name, ShaderType type);
	static unsigned int LinkShaders(unsigned int vertex, unsigned int fragment);

	// Integer uniforms
	void SetUniform1i(const std::string& name, int val);
	void SetUniform2i(const std::string& name, const glm::ivec2& value);
	void SetUniform3i(const std::string& name, const glm::ivec3& value);
	void SetUniform4i(const std::string& name, const glm::ivec4& value);

	// Unsigned Integer Uniforms
	void SetUniform1ui(const std::string& name, unsigned int val);
	void SetUniform2ui(const std::string& name, const glm::uvec2& value);
	void SetUniform3ui(const std::string& name, const glm::uvec3& value);
	void SetUniform4ui(const std::string& name, const glm::uvec4& value);

	// Float Uniforms
	void SetUniform1f(const std::string& name, float val);
	void SetUniform2f(const std::string& name, const glm::vec2& value);
	void SetUniform3f(const std::string& name, const glm::vec3& value);
	void SetUniform4f(const std::string& name, const glm::vec4& value);

	// Matrix Uniforms (2x2, 3x3, 4x4)
	void SetUniformMatrix2fv(const std::string& name, const glm::mat2& matrix);
	void SetUniformMatrix3fv(const std::string& name, const glm::mat3& matrix);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);

	// Other Types (For Example, Vectors Or Arrays)
	void SetUniform1iv(const std::string& name, int count, const int* values);
	void SetUniform1fv(const std::string& name, int count, const float* values);
	void SetUniform3fv(const std::string& name, int count, const glm::vec3* values);

	void Bind() const;
	void Unbind() const;


	inline std::string GetName() { return this->name; }
	inline void SetName(const std::string& name) { this->name = name; }
	inline unsigned int GetId() { return id; }

private:
	std::string name;
	std::string vertex;
	std::string fragment;
	unsigned int id;
};

class Texture
{
private:
	unsigned int id;
	unsigned char* data;
	int width;
	int height;
	int nChannels;
	unsigned int textureIndex;
	std::string filePath;

public:
	Texture() = default;
	Texture(std::string path);
	Texture(unsigned char* data, int width, int height) {}
	~Texture(){}

public:
	void Bind(unsigned int tex = 0);
	void Unbind();

	inline unsigned int GetId() { return id; }
	inline unsigned int GetIndex() { return textureIndex; }
	inline std::string GetFilePath() { return this->filePath; }
};

