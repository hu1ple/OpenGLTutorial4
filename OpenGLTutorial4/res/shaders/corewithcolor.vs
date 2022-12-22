#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 Color;
uniform mat4 proj;
uniform mat4 transform;
uniform mat4 view;
void main()
{
	gl_Position = proj * view * transform * vec4(position, 1.0f);
	Color = color;
}