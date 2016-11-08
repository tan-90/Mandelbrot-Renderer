#pragma once

#include "Common.h"
#include "Shader.h"

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

	void Update();

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

	std::string m_Title ;

	GLFWwindow* m_Handle;
	Shader*     m_Shader;

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_VertexCount;
};