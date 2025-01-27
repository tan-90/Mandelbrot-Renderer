#version 400 core

layout (location = 0) in vec3 Position;

out highp vec3 FragPosition;

void main()
{
	gl_Position = vec4(Position, 1.0);
	FragPosition = Position;
}