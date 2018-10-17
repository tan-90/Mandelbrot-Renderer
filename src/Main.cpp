#include "Common.h"
#include "GraphCanvas.h"

int main()
{
	// TODO: move initialization to static class
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_DEPTH_TEST);


	// Initialize the input handler
	Input::GetInstance().Init();

	// Create a canvas that uses the Mandelbrot fragment shader
	GraphCanvas* Sandbox = new GraphCanvas(800, 600, "Mandelbrot", { -1.0f, 1.5f, -1.0f, 1.5f }, { 0.0005f, 0.25f });

	while (!Sandbox->ShouldClose())
	{
		Sandbox->Update();
	}

	glfwTerminate();	
	return 0;
}