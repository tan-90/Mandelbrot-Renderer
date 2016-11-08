#include "Common.h"
#include "Canvas.h"

int main()
{
	// TODO: move initialization to static class
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glEnable(GL_DEPTH_TEST);

	// Create a canvas that uses the Mandelbrot fragment shader
	Canvas* Sandbox = new Canvas(800, 600, "Mandelbrot");

	while (!Sandbox->ShouldClose())
	{
		Sandbox->Update();
	}

	glfwTerminate();	
	return 0;
}