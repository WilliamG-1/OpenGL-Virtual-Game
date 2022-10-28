#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>


class Shader
{
public:
	Shader();
	void readShaderFile(const std::string& fileName, std::string& shaderString);
	void initShaders(const std::string& vertexSource, const std::string& fragmentSource);
	void use();

	void setUniformVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3);
	void setUniform1f(const std::string& uniformName, float value);
	void setUniform1i(const std::string& uniformName, int value);
	void setUniformMat4f(const std::string& uniformName, const glm::mat4& matrix);
	GLuint getShaderProgram() const;
private:
	enum class ShaderType
	{
		VERTEX_SHADER = 0, FRAGMENT_SHADER
	} shaderType;

	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;

	void createShader(const std::string& shaderString, GLuint& shader, ShaderType type);
};
 
