#pragma once

#include "Common.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct ShaderSource
{
	std::string VertexSource;
	std::string FragSource;
};

/**
  * Basic shader class that handles vertex and fragment shader stages
  */
class Shader
{
public:
	Shader(std::string VertexPath, std::string FragPath);
	~Shader();

	void Enable();
	static void Disable();
private:
	static ShaderSource FromFile(std::string VertexPath, std::string FragPath);
	static bool Compile(GLuint* Handle, ShaderSource Source);

	GLuint m_Handle;
};
