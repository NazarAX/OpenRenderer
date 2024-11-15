#include "Abstractions.h"
#include <GL/glew.h>
#include <memory.h>
#include "../Utils.h"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION  
#include <stb/stb_image.h>




VertexArray::VertexArray(VAData layout, float* data, unsigned int size)
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	unsigned int stride = sizeof(float) * (layout.colors + layout.coords + layout.normalCoords + layout.texCoords);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, layout.coords, GL_FLOAT, GL_FALSE, stride, 0);

	if (layout.colors)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, layout.colors, GL_FLOAT, GL_FALSE, stride, (void*) (sizeof(float) * layout.coords));
	}

	if (layout.texCoords)
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, layout.texCoords, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (layout.coords + layout.colors)));
	}

	if (layout.normalCoords)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, layout.normalCoords, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (layout.coords + layout.colors + layout.texCoords)));
	}

}


void VertexArray::Bind()
{
	glBindVertexArray(id);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}












IndexBuffer::IndexBuffer(unsigned int* data, int count) : count(count)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}


void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


Shader::Shader(const std::string& filename)
{
	std::string src = File::readFile(filename);
	vertex = parseShader(src, ShaderType::Vertex);
	fragment = parseShader(src, ShaderType::Fragment);

	size_t start = filename.find_last_of("/") + 1;
	size_t end = filename.find_last_of(".");
	this->name = filename.substr(start, end - start);


	unsigned int vertexShader = compileShader(vertex, name, ShaderType::Vertex);
	unsigned int fragmentShader = compileShader(fragment, name, ShaderType::Fragment);

	this->id = linkShaders(vertexShader, fragmentShader);

}
















Shader::Shader(const std::string& _vertex, const std::string& _fragment, const std::string& _name) : vertex(_vertex), fragment(_fragment), name(_name)
{
	unsigned int vertexShader = compileShader(_vertex, name, ShaderType::Vertex);
	unsigned int fragmentShader = compileShader(_fragment, name, ShaderType::Fragment);

	this->id = linkShaders(vertexShader, fragmentShader);
}

std::string Shader::parseShader(const std::string& src, ShaderType type)
{
	std::string define = (type == ShaderType::Vertex) ? "#define VERTEX\n" : "#define FRAGMENT\n";
	std::stringstream stream;
	stream << "#version 330\n";
	stream << define;
	stream << src;
	return stream.str();
}

unsigned int Shader::compileShader(std::string _src, const std::string& name, ShaderType type)
{
	GLuint shaderType = (type == Vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER;

	unsigned int shader = glCreateShader(shaderType);
	const char* src = _src.c_str();
	glShaderSource(shader, 1, &src, 0);
	glCompileShader(shader);

	GLint isSuccess;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &isSuccess);
	if (!isSuccess)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Error compiling " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " component of shader " << name << " : " << infoLog << std::endl;
	}

	return shader;
}


unsigned int Shader::linkShaders(unsigned int vertex, unsigned int fragment)
{
	unsigned int id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	GLint isLinked;
	glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
	if (!isLinked) {
		char infoLog[512];
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "Shader program linking error: " << infoLog << std::endl;
	}

	return id;
}


void Shader::bind()
{
	glUseProgram(id);
}
void Shader::unbind()
{
	glUseProgram(0);
}




void Shader::setUniform1i(const std::string& name, int val) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), val);
}

void Shader::setUniform2i(const std::string& name, const glm::ivec2& value) {
	glUniform2i(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setUniform3i(const std::string& name, const glm::ivec3& value) {
	glUniform3i(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setUniform4i(const std::string& name, const glm::ivec4& value) {
	glUniform4i(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setUniform1ui(const std::string& name, unsigned int val) {
	glUniform1ui(glGetUniformLocation(id, name.c_str()), val);
}

void Shader::setUniform2ui(const std::string& name, const glm::uvec2& value) {
	glUniform2ui(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setUniform3ui(const std::string& name, const glm::uvec3& value) {
	glUniform3ui(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setUniform4ui(const std::string& name, const glm::uvec4& value) {
	glUniform4ui(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setUniform1f(const std::string& name, float val) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), val);
}

void Shader::setUniform2f(const std::string& name, const glm::vec2& value) {
	glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setUniform3f(const std::string& name, const glm::vec3& value) {
	glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setUniform4f(const std::string& name, const glm::vec4& value) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setUniformMatrix2fv(const std::string& name, const glm::mat2& matrix) {
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformMatrix3fv(const std::string& name, const glm::mat3& matrix) {
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform1iv(const std::string& name, int count, const int* values) {
	glUniform1iv(glGetUniformLocation(id, name.c_str()), count, values);
}

void Shader::setUniform1fv(const std::string& name, int count, const float* values) {
	glUniform1fv(glGetUniformLocation(id, name.c_str()), count, values);
}

void Shader::setUniform3fv(const std::string& name, int count, const glm::vec3* values) {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), count, glm::value_ptr(*values));
}



Texture::Texture(std::string path)
{
	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // Horizontal wrapping (S axis)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // Vertical wrapping (T axis)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minifying filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnifying filter

	data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);

	if (data)
	{
		if (nChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}

}

void Texture::bind(unsigned int tex)
{
	textureId = tex;
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture()
{
	stbi_image_free(data);
}