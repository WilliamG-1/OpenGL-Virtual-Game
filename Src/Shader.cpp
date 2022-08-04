#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader()
	:
	program(0), vertexShader(0), fragmentShader(0)
{
	// We create the program that will be used for our shaders
	program = glCreateProgram();
}

void Shader::readShaderFile(const std::string& fileName, std::string& shaderString)
{
	// First, clear the shader string (in case there is garbage there lol)
	shaderString = "";
	// Open the file
	std::ifstream inFile(fileName);
	// Inital string variable to read line
	// read the input line by line
	for (std::string line = ""; std::getline(inFile, line);)
	{
		// Append the read line plus the newline character to the shader string
		shaderString += (line + '\n');
	}
	// Print it out lol
	// std::cout << shaderString << std::endl;
}

void Shader::createShader(const std::string& shaderString, GLuint& shader, ShaderType type)
{
	// First, we convert our std::string into a c string (OpenGL reading uses this as a parameter lol)
	const char* source = shaderString.c_str();

	// Depending on the type of shader, we specify a different parameter for glCreateShader
	switch (type)
	{
		// Create the vertex shader
	case ShaderType::VERTEX_SHADER:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;

		// Create the fragment shader
	case ShaderType::FRAGMENT_SHADER:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}
	// Extracts and creates the shader based on the shader source code passes. We specify:
	// 1.) The Shader
	// 2.) Number of shaders created
	// 3.) A memory address of the pointer of the source
	// 4.) The size of source, because we want the entire thing, we set nullptr
	glShaderSource(shader, 1, &source, nullptr);
	
	// Finally, we compile the shader
	glCompileShader(shader);

	// Check for shader compilation status
	int status;
	int length;
	char infoLog[1024];
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderInfoLog(shader, 1024, &length, infoLog);
		std::cout << (type == ShaderType::VERTEX_SHADER ? "vertex: " : "fragment ") << " failed to compile!\n" << infoLog << std::endl;
		glDeleteShader(shader);
	}


}

void Shader::initShaders(const std::string& vertexSource, const std::string& fragmentSource)
{
	// We create our two basic shaders
	createShader(vertexSource, vertexShader, ShaderType::VERTEX_SHADER);
	createShader(fragmentSource, fragmentShader, ShaderType::FRAGMENT_SHADER);

	// Attatch the shaders to the shader program (Done before linking). This tells OpenGL
	// what will be linked (Sort of puts them in a queue).
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Finally, we link everything to the program (specified by glattachshader)
	glLinkProgram(program);
	glValidateProgram(program);
	// Now, we can delete the shaders since they are already linked lol.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::use()
{
	// We activate our program by calling glUseProgram. This is the current program that will be used
	// for our current rendering state
	glUseProgram(program);
}

void Shader::setUniformVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(program, uniformName.c_str()), v0, v1, v2, v3);
}

void Shader::setUniform1f(const std::string& uniformName, float value)
{
	glUniform1f(glGetUniformLocation(program, uniformName.c_str()), value);
}

void Shader::setUniform1i(const std::string& uniformName, int value)
{
	glUniform1i(glGetUniformLocation(program, uniformName.c_str()), value);
}

void Shader::setUniformMat4f(const std::string& uniformName, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(program, uniformName.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

GLuint Shader::getShaderProgram() const
{
	return program;
}