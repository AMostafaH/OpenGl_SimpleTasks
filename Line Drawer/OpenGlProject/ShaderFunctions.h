#pragma once
// This code will be used as copy -> paste in all your projects
#include <glew/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;

static char* readFile(const char* fileName)
{
	ifstream shaderfile(fileName, ios::ate);//ate-> at the end
	if (!shaderfile.is_open())
	{
		cerr << "OpenFileError File:" << fileName;
		return NULL;
	}
	streampos size = shaderfile.tellg();
	char* filedata = new char[size];
	for (int i = 0; i < size; i++)
		filedata[i] = 0;
	shaderfile.seekg(ios::beg);
	shaderfile.read(filedata, size);
	shaderfile.close();
	return filedata;
}

bool compiledStatus(GLint shaderID) {
	GLint compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled)
		return true;
	else
	{
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* msgBuffer = new char[logLength];
		glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
		printf("%s\n", msgBuffer);
		delete(msgBuffer);
		return false;
	}
}

GLuint makeShader(const char* ShaderSourceCode, GLenum SHADER_TYPE) // used for vertex and fragment shader
{
	GLuint shaderID = glCreateShader(SHADER_TYPE); // it creates shader on Gpu upon the type you selected
	glShaderSource(shaderID, 1, (const GLchar**)&ShaderSourceCode, NULL); // send the created shader file to be compiled
	glCompileShader(shaderID);
	bool compiledCorrectly = compiledStatus(shaderID);
	if (compiledCorrectly)
		return shaderID; // if compilation succeded return ID
	else
		return -1;		// if compilation failed return -1
}
GLuint makeShaderProgram(GLuint vertShaderID, GLuint fragShaderID)
{
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertShaderID);
	glAttachShader(shaderID, fragShaderID);
	glLinkProgram(shaderID);
	return shaderID;
}
GLuint InitShader(const char* vertex_shader_file_name, const char* fragment_shader_file_name)
{
	char* vertexShaderSourceCode = readFile(vertex_shader_file_name);
	char* fragmentShaderSourceCode = readFile(fragment_shader_file_name);
	GLuint vertexShaderID = makeShader(vertexShaderSourceCode, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = makeShader(fragmentShaderSourceCode, GL_FRAGMENT_SHADER);
	GLuint shaderProgramID = makeShaderProgram(vertexShaderID, fragmentShaderID);
	printf("Vertex Shader ID:%d", vertexShaderID);
	printf("\nFragment Shader ID:%d", fragmentShaderID);
	printf("\nshaderProgramID:%d", shaderProgramID);
	return shaderProgramID;
}

