#include "Canvas.h"

Canvas::Canvas(uint Width, uint Height, std::string Title)
{
	m_Title = Title;
	m_Handle = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);	
	// TODO: handle window creation failure

	glfwMakeContextCurrent(m_Handle);
	glewExperimental = GL_TRUE;
	glewInit() != GLEW_OK;
	// TODO: handle glew initialization failure

	glViewport(0, 0, Width, Height);

	// Only one canvas should be active at a time, with only one shader
	// Shader, buffer and context binding and unbinding is expensive and should be avoided in this case
	SetupShaders();
	m_Shader->Enable();

	SetupCanvas();

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}

Canvas::~Canvas()
{
	// Disable and clean up used resources
	Shader::Disable();
	delete m_Shader;

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteVertexArrays(1, &m_VAO);

	glfwDestroyWindow(m_Handle);
}

void Canvas::Update()
{
	glfwPollEvents();

	Render();

	glfwSwapBuffers(m_Handle);
}

bool Canvas::ShouldClose() const
{
	return glfwWindowShouldClose(m_Handle) != 0;
}

void Canvas::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, 0);
}

void Canvas::SetupShaders()
{
	// If not overriden, use the default shaders
	m_Shader = new Shader(
		"src/shaders/vert/Common.glsl",
		"src/shaders/frag/" + m_Title + ".glsl"
		);
}

void Canvas::SetupCanvas()
{
	// Sets a default quad that covers the viewport as the mesh to be rendered
	GLfloat Vertices[] =
	{
		 1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f
	};

	GLuint Indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	
	glBindVertexArray(NULL);

	m_VertexCount = 6;
}

void Canvas::LoadUniforms()
{
	// NOOP
}

GLint Canvas::GetUniformLocation(std::string Location)
{
	return glGetUniformLocation(m_Shader->GetHandle(), (GLchar*)Location.c_str());
}

void Canvas::LoadUniformFloat(std::string Location, GLfloat Uniform)
{
	glUniform1f(GetUniformLocation(Location), Uniform);
}
