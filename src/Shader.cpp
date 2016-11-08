#include "Shader.h"

Shader::Shader(std::string VertexPath, std::string FragPath)
{
	ShaderSource Source;

	Source = Shader::FromFile(VertexPath, FragPath);
	Shader::Compile(&m_Handle, Source);
	// TODO: handle compilation failure
}

Shader::~Shader()
{
	glDeleteShader(m_Handle);
}

void Shader::Enable()
{
	glUseProgram(m_Handle);
}
void Shader::Disable()
{
	glUseProgram(NULL);
}

ShaderSource Shader::FromFile(std::string VertexPath, std::string FragPath)
{
	// TODO: use C style file reading
	ShaderSource Source;

	std::string VertexSource;
	std::string FragSource;

	std::ifstream VertexFile;
	std::ifstream FragFile;

	std::stringstream VertexStream;
	std::stringstream FragStream;

	VertexFile.open(VertexPath);
	FragFile.open(FragPath);

	VertexStream << VertexFile.rdbuf();
	FragStream << FragFile.rdbuf();

	VertexFile.close();
	FragFile.close();

	VertexSource = VertexStream.str();
	FragSource = FragStream.str();

	Source.VertexSource = VertexSource;
	Source.FragSource = FragSource;

	return Source;
}

bool Shader::Compile(GLuint* Handle, ShaderSource Source)
{
	GLint  ShaderStatus;
	GLchar ErrorInfo[512];

	GLchar* VertexSource;
	GLchar* FragSource;

	VertexSource = (GLchar*)Source.VertexSource.c_str();
	FragSource   = (GLchar*)Source.FragSource.c_str();

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexSource, NULL);
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &ShaderStatus);
	if (!ShaderStatus)
	{
		glGetShaderInfoLog(VertexShader, 512, NULL, ErrorInfo);
		std::cout << "Vertex shader compilation error: " << std::endl;
		std::cout << ErrorInfo << std::endl;
		return false;
	}

	GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader, 1, &FragSource, NULL);
	glCompileShader(FragShader);
	glGetShaderiv(FragShader, GL_COMPILE_STATUS, &ShaderStatus);
	if (!ShaderStatus)
	{
		glGetShaderInfoLog(FragShader, 512, NULL, ErrorInfo);
		std::cout << "Fragment shader compilation error: " << std::endl;
		std::cout << ErrorInfo << std::endl;
		return false;
	}

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragShader);
	
	glDeleteShader(VertexShader);
	glDeleteShader(FragShader);

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &ShaderStatus);
	if (!ShaderStatus)
	{
		glGetProgramInfoLog(ShaderProgram, 512, NULL, ErrorInfo);
		std::cout << "Program link error: " << std::endl;
		std::cout << ErrorInfo << std::endl;
		return false;
	}

	*Handle = ShaderProgram;
	return true;
}
