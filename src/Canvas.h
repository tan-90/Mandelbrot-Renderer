#pragma once

#include "Common.h"
#include "Shader.h"
#include "Input.h"

#include <string>

/**
  * Base canvas class. Draws a default quad that covers the screen.
  * The name of the canvas is used to get the fragment shader used for the quad.
  */
class Canvas
{
public:
	Canvas(uint Width, uint Height, std::string Name);
	~Canvas();

	/**
	  * Can be overriden for input handling or animation.
	  */
	virtual void Update();

	bool ShouldClose() const;

protected:
	/**
	  * Can be overriden for custom rendering modes.
	  */
	virtual void Render();
	/**
	  * Can be overriden to use more complex shaders stages.
	  */
	virtual void SetupShaders();
	/**
	  * Can be overriden to change the mesh that is being rendered.
	  * By default the canvas renders it's member VAO with the IBO.
	  */
	virtual void SetupCanvas ();

	/**
	  * Needs to be overriden for uniforms to work.
	  * Use the GetUniformLocation and SetUniform methods to load values.
	  * This is not called by default.
	  */
	virtual void LoadUniforms();

	GLint GetUniformLocation(std::string Location);
	void LoadUniformFloat(std::string Location, GLfloat Uniform);

	std::string m_Title ;

	GLFWwindow* m_Handle;
	Shader*     m_Shader;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_VertexCount;
};